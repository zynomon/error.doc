---
layout: default
title: "Search"
description: "Search across every page of the error.os documentation"
---

# Search

<div id="search-app" data-site="{{ '/' | absolute_url }}" data-repo="zynomon/error.doc" data-branch="main" data-dir="docs/">
  <input class="s-input" id="s-input" type="search" placeholder="search across all docs" autocomplete="off" aria-label="Search all docs" disabled>
  <div class="s-load" id="s-load">
    <p class="s-status" id="s-status" role="status">loading docs .. 0/0</p>
    <div class="s-bar"><span id="s-bar"></span></div>
  </div>
  <p class="s-count" id="s-count" aria-live="polite"></p>
  <div id="s-results"></div>
</div>

<script>
(function () {
  var app = document.getElementById('search-app'), input = document.getElementById('s-input');
  var status = document.getElementById('s-status'), bar = document.getElementById('s-bar');
  var load = document.getElementById('s-load');
  var count = document.getElementById('s-count'), out = document.getElementById('s-results');
  var repo = app.dataset.repo, branch = app.dataset.branch, dir = app.dataset.dir, site = app.dataset.site;
  var RAW = 'https://raw.githubusercontent.com/' + repo + '/' + branch + '/';
  var KEY = 'errdoc-search:v1:' + repo + '@' + branch;
  var link = document.querySelector('link[rel~="icon"]');
  var fallbackIcon = link ? link.href : '';
  var WORD = /[\p{L}\p{N}]{3,}/gu;
  var index = [], files = 0, done = 0, failed = 0, total = 0, limited = false, note = '';
  var vocab = null, typeTimer = 0, dymTimer = 0, dymTok = 0, dym = null, retry = null;

  var esc = function (s) { return String(s).replace(/[&<>"]/g, function (c) { return { '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]; }); };
  var rx  = function (s) { return s.replace(/[.*+?^$()|[\]\\{}]/g, '\\$&'); };
  var slug = function (t) { return t.toLowerCase().replace(/[^a-z0-9 -]/g, '').replace(/ /g, '-').replace(/^[^a-z]+/, ''); };
  var enc = function (p) { return p.split('/').map(encodeURIComponent).join('/'); };
  var safe = function (u) { return /^\s*(javascript|data|vbscript):/i.test(u) ? '' : u; };

  var DOC_RX = new RegExp('^' + rx(dir) + '[^/]+/[^/]+\\.md$', 'i');

  function get(url, type) {
    var c = new AbortController(), t = setTimeout(function () { c.abort(); }, 12000);
    return fetch(url, { signal: c.signal }).then(function (r) {
      clearTimeout(t);
      if (!r.ok) { var e = new Error('http ' + r.status); e.status = r.status; throw e; }
      return r[type]();
    }, function (e) { clearTimeout(t); throw e; });
  }

  function list() {
    limited = false;
    return get('https://api.github.com/repos/' + repo + '/git/trees/' + branch + '?recursive=1', 'json')
      .then(function (t) {
        if (t.truncated) throw new Error('truncated');
        return t.tree.filter(function (f) { return f.type === 'blob'; }).map(function (f) { return { p: f.path, h: f.sha }; });
      })
      .catch(function (err) {
        limited = !!err && (err.status === 403 || err.status === 429);
        return get('https://data.jsdelivr.com/v1/package/gh/' + repo + '@' + branch + '/flat', 'json')
          .then(function (d) { limited = false; return d.files.map(function (f) { return { p: f.name.replace(/^\//, ''), h: f.hash }; }); });
      })
      .then(function (all) { return all.filter(function (i) { return DOC_RX.test(i.p); }); });
  }

  function readCache() {
    try { var c = JSON.parse(localStorage.getItem(KEY)); return c && c.f ? c : { f: {} }; } catch (e) { return { f: {} }; }
  }
  function writeCache(f) {
    try { localStorage.setItem(KEY, JSON.stringify({ t: Date.now(), f: f })); } catch (e) {}
  }

  var LIQUID = new RegExp('\\x7b[\\x7b%][\\s\\S]*?[\\x7d%]\\x7d', 'g');
  function clean(l) {
    return l.replace(/<[^>]*>/g, ' ').replace(LIQUID, ' ').replace(/\{:[^}]*\}/g, ' ')
      .replace(/!\[([^\]]*)\]\([^)]*\)/g, '$1').replace(/\[([^\]]*)\]\([^)]*\)/g, '$1')
      .replace(/^\s*>\s*(\[![A-Z]+\])?/, '').replace(/^\s*([-*+]|\d+\.)\s+/, '').replace(/[`*_|~]/g, ' ');
  }
  function parse(path, md) {
    var ents = [], used = {}, meta = {}, fm = md.match(/^---\r?\n([\s\S]*?)\r?\n---\r?\n?/);
    if (fm) {
      fm[1].split(/\r?\n/).forEach(function (l) { var m = l.match(/^([\w-]+):\s*["']?(.*?)["']?\s*$/); if (m) meta[m[1]] = m[2]; });
      md = md.slice(fm[0].length);
    }
    var id = path.replace(/\.md$/i, '').replace(/\/index$/i, '');
    var url = site + (meta.permalink ? meta.permalink.replace(/^\//, '') : /(^|\/)index\.md$/i.test(path) ? path.replace(/index\.md$/i, '') : path.replace(/\.md$/i, '.html'));
    var icon = safe(meta.icon || fallbackIcon);
    var title = meta.title || id;
    var sec = { h: title, a: '', t: [] }, seen = false, fence = false;
    function uniq(a) {
      if (!a) return a;
      if (used[a] === undefined) { used[a] = 0; return a; }
      used[a]++; return a + '-' + used[a];
    }
    function flush() {
      var t = sec.t.join(' ').replace(/\s+/g, ' ').trim();
      if (t || sec.a) ents.push({ id: id, title: title, sh: sec.h, url: url + (sec.a ? '#' + sec.a : ''), icon: icon, text: t, hl: sec.h.toLowerCase(), tl: t.toLowerCase() });
    }
    md.split(/\r?\n/).forEach(function (l) {
      if (/^\s*(```|~~~)/.test(l)) { fence = !fence; return; }
      var h = !fence && l.match(/^#{1,6}\s+(.+?)\s*#*\s*$/);
      if (h) {
        var ial = h[1].match(/\s*\{#([\w-]+)\}\s*$/), text = clean(h[1].replace(/\s*\{#[\w-]+\}\s*$/, '')).trim();
        var a = ial ? ial[1] : uniq(slug(text));
        if (!seen && !meta.title && !sec.t.length) { sec.h = text; sec.a = a; } else { flush(); sec = { h: text, a: a, t: [] }; }
        seen = true;
      } else if (!/^\s*[-*+]\s+\[[^\]]*\]\(#[^)]*\)\s*$/.test(l) && !/^\s*\|?[\s:|-]+\|?\s*$/.test(l)) sec.t.push(fence ? l : clean(l));
    });
    flush();
    return ents;
  }

  function progress() {
    status.textContent = 'loading docs .. ' + done + '/' + total;
    bar.style.width = (total ? done / total * 100 : 100) + '%';
  }
  function pool(items, n, fn) {
    var i = 0;
    function w() {
      if (i >= items.length) return Promise.resolve();
      return fn(items[i++]).then(function () { done++; progress(); }).then(w);
    }
    var ws = [];
    for (var k = 0; k < Math.min(n, items.length); k++) ws.push(w());
    return Promise.all(ws);
  }
  function showRetry(show) {
    if (!retry) {
      retry = document.createElement('button');
      retry.type = 'button'; retry.className = 's-retry'; retry.textContent = 'retry';
      retry.addEventListener('click', start);
      load.appendChild(retry);
    }
    retry.hidden = !show;
  }

  function start() {
    showRetry(false);
    load.hidden = false; bar.parentNode.hidden = false;
    done = 0; failed = 0; total = 0; note = ''; progress();
    var cache = readCache(), fresh = {}, stale = 0;
    list().then(function (items) {
      total = items.length; progress();
      return pool(items, 6, function (it) {
        var c = cache.f[it.p];
        if (c && c.h && c.h === it.h) { fresh[it.p] = c; return Promise.resolve(); }
        return get(RAW + enc(it.p), 'text')
          .then(function (md) { fresh[it.p] = { h: it.h, e: parse(it.p, md) }; })
          .catch(function () { if (c) { fresh[it.p] = c; stale++; } else failed++; });
      }).then(function () { if (stale) note = ' ( ' + stale + ' served from cache )'; finish(fresh, true); });
    }, function () {
      if (Object.keys(cache.f).length) {
        note = limited ? ' ( github rate limit, showing cached copy )' : ' ( offline, showing cached copy )';
        finish(cache.f, false);
      } else finish({}, false);
    });
  }

  function finish(fresh, save) {
    var keys = Object.keys(fresh).sort();
    index = []; files = 0; vocab = null;
    keys.forEach(function (p) { index = index.concat(fresh[p].e); files++; });
    if (save && files) writeCache(fresh);
    if (!files) {
      status.textContent = limited ? 'github rate limit reached, try again later' : 'could not load the docs from github';
      bar.parentNode.hidden = true; showRetry(true); count.textContent = '';
      return;
    }
    if (failed) {
      status.textContent = failed + ' file' + (failed > 1 ? 's' : '') + ' failed to load';
      bar.parentNode.hidden = true; showRetry(true);
    } else load.hidden = true;
    input.disabled = false;
    if (!document.activeElement || document.activeElement === document.body) input.focus();
    var q = new URLSearchParams(location.search).get('q');
    if (q && !input.value) input.value = q;
    run();
  }

  function buildVocab() {
    vocab = new Map();
    index.forEach(function (e) {
      (e.hl + ' ' + e.tl).match(WORD) && (e.hl + ' ' + e.tl).match(WORD).forEach(function (w) { vocab.set(w, (vocab.get(w) || 0) + 1); });
    });
  }
  function dist(a, b, max) {
    var al = a.length, bl = b.length, prev2 = null, prev = [], cur, i, j;
    if (Math.abs(al - bl) > max) return max + 1;
    for (j = 0; j <= bl; j++) prev[j] = j;
    for (i = 1; i <= al; i++) {
      cur = [i]; var rowMin = i;
      for (j = 1; j <= bl; j++) {
        var v = Math.min(prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + (a[i - 1] === b[j - 1] ? 0 : 1));
        if (i > 1 && j > 1 && a[i - 1] === b[j - 2] && a[i - 2] === b[j - 1]) v = Math.min(v, prev2[j - 2] + 1);
        cur[j] = v; if (v < rowMin) rowMin = v;
      }
      if (rowMin > max) return max + 1;
      prev2 = prev; prev = cur;
    }
    return prev[bl];
  }
  function known(w) {
    return index.some(function (e) { return e.hl.indexOf(w) > -1 || e.tl.indexOf(w) > -1; });
  }
  function closest(w) {
    var max = w.length >= 6 ? 2 : 1, best = null, bd = max + 1, bc = 0;
    vocab.forEach(function (c, v) {
      if (v === w) return;
      var d = dist(w, v, max);
      if (d < bd || (d === bd && c > bc)) { best = v; bd = d; bc = c; }
    });
    return bd <= max ? best : null;
  }
  function suggest(words) {
    clearTimeout(dymTimer);
    var tok = ++dymTok;
    if (dym) { dym.hidden = true; dym.innerHTML = ''; }
    dymTimer = setTimeout(function () {
      if (tok !== dymTok) return;
      if (!vocab) buildVocab();
      var changed = false, fixed = words.map(function (w) {
        if (w.length < 4 || known(w)) return w;
        var c = closest(w);
        if (c) { changed = true; return c; }
        return w;
      });
      if (!changed || tok !== dymTok) return;
      if (!dym) {
        dym = document.createElement('p');
        dym.className = 's-dym';
        count.parentNode.insertBefore(dym, count.nextSibling);
        dym.addEventListener('click', function (e) {
          var a = e.target.closest('a');
          if (!a) return;
          e.preventDefault(); input.value = a.dataset.q; run(); input.focus();
        });
      }
      var s = fixed.join(' ');
      dym.innerHTML = 'did you mean <a href="?q=' + encodeURIComponent(s) + '" data-q="' + esc(s) + '">' + esc(s) + '</a>?';
      dym.hidden = false;
    }, 250);
  }

  function run() {
    var q = input.value.trim(), words = q.toLowerCase().split(/\s+/).filter(Boolean);
    history.replaceState(null, '', (q ? '?q=' + encodeURIComponent(q) : location.pathname) + location.hash);
    if (!words.length) {
      count.textContent = index.length + ' sections in ' + files + ' docs' + note;
      out.innerHTML = ''; suggest([]); return;
    }
    var hits = [];
    index.forEach(function (e, n) {
      var s = 0;
      for (var i = 0; i < words.length; i++) {
        var h = e.hl.indexOf(words[i]) > -1, t = e.tl.indexOf(words[i]) > -1;
        if (!h && !t) return;
        s += (h ? 5 : 0) + (t ? 1 : 0);
      }
      hits.push({ e: e, s: s, n: n });
    });
    hits.sort(function (a, b) { return b.s - a.s || a.n - b.n; });
    count.textContent = (hits.length ? hits.length + ' found' + (hits.length > 60 ? ' ( showing 60 )' : '') : 'nothing found') + note;
    var re = new RegExp('(' + words.map(rx).join('|') + ')', 'i');
    out.innerHTML = hits.slice(0, 60).map(function (h) {
      var e = h.e, p = -1;
      for (var i = 0; i < words.length && p < 0; i++) p = e.tl.indexOf(words[i]);
      var from = Math.max(0, p < 0 ? 0 : p - 40);
      var snip = (from ? '…' : '') + e.text.slice(from, from + 140) + (from + 140 < e.text.length ? '…' : '');
      var mark = snip.split(re).map(function (v, i) { return i % 2 ? '<mark>' + esc(v) + '</mark>' : esc(v); }).join('');
      var img = e.icon ? '<img src="' + esc(e.icon) + '" alt="" loading="lazy" onerror="this.style.visibility=\'hidden\'">' : '';
      return '<a class="hit" href="' + esc(e.url) + '">' + img + '<b>' + esc(e.title) + (e.sh && e.sh !== e.title ? ' › ' + esc(e.sh) : '') + '</b>:<span>' + mark + '</span></a>';
    }).join('');
    suggest(words);
  }

  input.addEventListener('input', function () { clearTimeout(typeTimer); typeTimer = setTimeout(run, 80); });
  app.addEventListener('keydown', function (e) {
    if (e.key === 'Enter' && document.activeElement === input) { clearTimeout(typeTimer); run(); if (out.firstChild) out.firstChild.click(); return; }
    var l = [].slice.call(out.children), i = l.indexOf(document.activeElement);
    if (e.key === 'ArrowDown') { e.preventDefault(); (l[i + 1] || l[0] || input).focus(); }
    else if (e.key === 'ArrowUp') { e.preventDefault(); (i > 0 ? l[i - 1] : input).focus(); }
  });

  start();
})();
</script>