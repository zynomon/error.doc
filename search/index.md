---
layout: default
title: "Search"
description: "Search across every page of the error.os documentation"
---

<div align="center">
  <h1>Search Across The Documentation.</h1>
  <input id="s-input" type="search" placeholder="search.." autocomplete="off" disabled style="width:100%;max-width:600px;padding:0.75rem;border:1px solid rgba(128,128,128,0.3);background:transparent;color:inherit;font-family:inherit;box-sizing:border-box;">
  <br>
  <progress id="s-bar" style="width:100%;max-width:600px;height:4px;margin-top:1rem;"></progress>
  <br>
  <span id="s-status" style="display:block;margin-top:0.5rem;color:rgba(128,128,128,0.7)">0/0 loaded....</span>
</div>

<div id="s-results" style="max-width:600px;margin:2rem auto;text-align:left"></div>

<script>
(function () {
  var input = document.getElementById('s-input');
  var bar = document.getElementById('s-bar');
  var status = document.getElementById('s-status');
  var out = document.getElementById('s-results');

  var C = window.ERROR_DOC || {};
  var repo = 'zynomon/error.doc';
  var branch = 'main';
  var dir = 'docs/';

  var site = new URL(C.home || '/', location.origin).href;
  if (site.slice(-1) !== '/') site += '/';

  var API = 'https://api.github.com/repos/' + repo + '/';
  var RAW = 'https://raw.githubusercontent.com/' + repo + '/';
  var KEY = 'errdoc-search:v2:' + repo + '@' + branch;

  var link = document.querySelector('link[rel~="icon"]');
  var DEFAULT = C.icon || (link ? link.href : '');

  var index = [], files = 0, done = 0, failed = 0, total = 0, limited = false, note = '';
  var vocab = null, typeTimer = 0, dymTimer = 0, dymTok = 0, dym = null, retry = null;

  var esc = function (s) { return String(s).replace(/[&<>"]/g, function (c) { return { '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]; }); };
  var rx  = function (s) { return s.replace(/[.*+?^$()|[\]\\{}]/g, '\\$&'); };
  var slug = function (t) { return t.toLowerCase().replace(/[^a-z0-9 -]/g, '').replace(/ /g, '-').replace(/^[^a-z]+/, ''); };
  var enc = function (p) { return p.split('/').map(encodeURIComponent).join('/'); };
  var safe = function (u) { return /^\s*(javascript|data|vbscript):/i.test(u) ? '' : u; };
  var WORD = /[\p{L}\p{N}]{3,}/gu;

  var DOC_RX = new RegExp('^' + rx(dir) + '[^/]+/[^/]+\\.md$', 'i');

  function get(url, type) {
    var c = new AbortController(), t = setTimeout(function () { c.abort(); }, 12000);
    return fetch(url, { signal: c.signal }).then(function (r) {
      clearTimeout(t);
      if (!r.ok) { var e = new Error('http ' + r.status); e.status = r.status; throw e; }
      return r[type]();
    }, function (e) { clearTimeout(t); throw e; });
  }
  function isLimit(err) { return !!err && (err.status === 403 || err.status === 429); }

  function head() {
    limited = false;
    return get(API + 'git/ref/heads/' + branch, 'json').then(function (d) { return d.object.sha; });
  }

  function list(sha) {
    var gh = sha
      ? get(API + 'git/trees/' + sha + '?recursive=1', 'json').then(function (t) {
          if (t.truncated) throw new Error('truncated');
          return t.tree.filter(function (f) { return f.type === 'blob'; }).map(function (f) { return { p: f.path, h: f.sha }; });
        })
      : Promise.reject(new Error('no sha'));
    return gh
      .catch(function (err) {
        if (isLimit(err)) limited = true;
        return get('https://data.jsdelivr.com/v1/package/gh/' + repo + '@' + (sha || branch) + '/flat', 'json')
          .then(function (d) { limited = false; return d.files.map(function (f) { return { p: f.name.replace(/^\//, ''), h: f.hash }; }); });
      })
      .then(function (all) { return all.filter(function (i) { return DOC_RX.test(i.p); }); });
  }

  function readCache() {
    try { var c = JSON.parse(localStorage.getItem(KEY)); return c && c.f ? c : { sha: null, f: {} }; } catch (e) { return { sha: null, f: {} }; }
  }
  function writeCache(sha, f) {
    try { localStorage.setItem(KEY, JSON.stringify({ sha: sha, t: Date.now(), f: f })); } catch (e) {}
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
    var rel = meta.permalink ? meta.permalink.replace(/^\//, '') : /(^|\/)index\.md$/i.test(path) ? path.replace(/index\.md$/i, '') : path.replace(/\.md$/i, '.html');
    var title = meta.title || id;
    var sec = { h: title, a: '', t: [] }, seen = false, fence = false;
    function uniq(a) {
      if (!a) return a;
      if (used[a] === undefined) { used[a] = 0; return a; }
      used[a]++; return a + '-' + used[a];
    }
    function flush() {
      var t = sec.t.join(' ').replace(/\s+/g, ' ').trim();
      if (t || sec.a) ents.push({ t: title, s: sec.h, a: sec.a, d: rel, i: meta.icon || '', x: t });
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

  function iconOf(ic, docUrl) {
    ic = safe(ic || '');
    if (!ic) return DEFAULT;
    try { return new URL(ic, docUrl).href; } catch (e) { return DEFAULT; }
  }
  function hydrate(e) {
    var doc = site + e.d;
    return { title: e.t, sh: e.s, url: doc + (e.a ? '#' + e.a : ''), icon: iconOf(e.i, doc), text: e.x, hl: e.s.toLowerCase(), tl: e.x.toLowerCase() };
  }

  function progress() {
    status.textContent = done + '/' + total + ' loaded....';
    if (total > 0) bar.value = done;
    else bar.removeAttribute('value');
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
      retry.type = 'button'; retry.textContent = 'retry';
      retry.addEventListener('click', start);
      status.parentNode.appendChild(retry);
    }
    retry.hidden = !show;
  }

  function start() {
    showRetry(false);
    bar.style.display = ''; status.style.display = '';
    bar.max = 0; bar.value = 0;
    done = 0; failed = 0; total = 0; note = ''; progress();
    var cache = readCache(), have = Object.keys(cache.f).length > 0;

    head().then(function (sha) {
      if (have && cache.sha === sha) { finish(cache.f); return; }
      sync(sha, cache, have);
    }, function (err) {
      limited = isLimit(err);
      if (have) { note = limited ? ' (rate limit, cached)' : ' (offline, cached)'; finish(cache.f); return; }
      sync(null, cache, false);
    });
  }

  function sync(sha, cache, have) {
    var fresh = {}, stale = 0, base = RAW + (sha || branch) + '/';
    list(sha).then(function (items) {
      total = items.length; bar.max = total; progress();
      return pool(items, 6, function (it) {
        var c = cache.f[it.p];
        if (c && c.h && c.h === it.h) { fresh[it.p] = c; return Promise.resolve(); }
        return get(base + enc(it.p), 'text')
          .then(function (md) { fresh[it.p] = { h: it.h, e: parse(it.p, md) }; })
          .catch(function () { if (c) { fresh[it.p] = c; stale++; } else failed++; });
      }).then(function () {
        if (stale) note = ' (' + stale + ' cached)';
        if (Object.keys(fresh).length) writeCache(failed || stale ? null : sha, fresh);
        finish(fresh);
      });
    }, function () {
      if (have) { note = limited ? ' (rate limit, cached)' : ' (offline, cached)'; finish(cache.f); } else finish({});
    });
  }

  function finish(fresh) {
    index = []; files = 0; vocab = null;
    Object.keys(fresh).sort().forEach(function (p) {
      fresh[p].e.forEach(function (e) { index.push(hydrate(e)); });
      files++;
    });
    if (!files) {
      status.textContent = limited ? 'github rate limit reached' : 'could not load docs';
      bar.style.display = 'none'; showRetry(true);
      return;
    }
    if (failed) {
      status.textContent = failed + ' file(s) failed';
      bar.style.display = 'none'; showRetry(true);
    } else {
      status.style.display = 'none';
      bar.style.display = 'none';
    }
    input.disabled = false;
    if (!document.activeElement || document.activeElement === document.body) input.focus();
    var q = new URLSearchParams(location.search).get('q');
    if (q && !input.value) input.value = q;
    run();
  }

  function buildVocab() {
    vocab = new Map();
    index.forEach(function (e) {
      var m = (e.hl + ' ' + e.tl).match(WORD);
      if (m) m.forEach(function (w) { vocab.set(w, (vocab.get(w) || 0) + 1); });
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
    if (dym) { dym.remove(); dym = null; }
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
      var s = fixed.join(' ');
      dym = document.createElement('p');
      dym.style.textAlign = 'center';
      dym.innerHTML = 'did you mean <a href="?q=' + encodeURIComponent(s) + '">' + esc(s) + '</a>?';
      dym.querySelector('a').addEventListener('click', function (e) {
        e.preventDefault(); input.value = s; run(); input.focus();
      });
      out.parentNode.insertBefore(dym, out);
    }, 250);
  }

  function run() {
    var q = input.value.trim(), words = q.toLowerCase().split(/\s+/).filter(Boolean);
    history.replaceState(null, '', (q ? '?q=' + encodeURIComponent(q) : location.pathname) + location.hash);
    if (dym) { dym.remove(); dym = null; }
    if (!words.length) {
      dymTok++;
      out.innerHTML = '<p style="text-align:center;color:rgba(128,128,128,0.7)">' + index.length + ' sections in ' + files + ' docs' + note + '</p>';
      return;
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

    if (!hits.length) {
      out.innerHTML = '<p style="text-align:center;color:rgba(128,128,128,0.7)">nothing found' + note + '</p>';
      suggest(words);
      return;
    }

    var re = new RegExp('(' + words.map(rx).join('|') + ')', 'i');
    out.innerHTML = hits.slice(0, 60).map(function (h) {
      var e = h.e, p = -1;
      for (var i = 0; i < words.length && p < 0; i++) p = e.tl.indexOf(words[i]);
      var from = Math.max(0, p < 0 ? 0 : p - 40);
      var snip = (from ? '…' : '') + e.text.slice(from, from + 140) + (from + 140 < e.text.length ? '…' : '');
      var mark = snip.split(re).map(function (v, i) { return i % 2 ? '<mark>' + esc(v) + '</mark>' : esc(v); }).join('');
      var img = e.icon ? '<img src="' + esc(e.icon) + '" alt="" width="20" height="20" loading="lazy" style="vertical-align:middle;margin-right:0.5em">' : '';
      return '<div style="border-bottom:1px solid rgba(128,128,128,0.3);padding:0.5em 0"><a class="hit" href="' + esc(e.url) + '" style="font-weight:bold;color:inherit;text-decoration:none">' + img + esc(e.title) + (e.sh && e.sh !== e.title ? ' › ' + esc(e.sh) : '') + '</a><br><span style="font-size:0.9em;color:rgba(128,128,128,0.8)">' + mark + '</span></div>';
    }).join('');
    suggest(words);
  }

  out.addEventListener('error', function (e) {
    var t = e.target;
    if (!t || t.tagName !== 'IMG') return;
    if (DEFAULT && !t.dataset.fb) { t.dataset.fb = '1'; t.src = DEFAULT; } else t.style.visibility = 'hidden';
  }, true);

  input.addEventListener('input', function () { clearTimeout(typeTimer); typeTimer = setTimeout(run, 80); });

  document.addEventListener('keydown', function (e) {
    var a = document.activeElement;
    if (a !== input && !out.contains(a)) return;
    if (e.key === 'Enter' && a === input) {
      clearTimeout(typeTimer); run();
      var first = out.querySelector('a.hit');
      if (first) first.click();
      return;
    }
    var l = [].slice.call(out.querySelectorAll('a.hit')), i = l.indexOf(a);
    if (e.key === 'ArrowDown') { e.preventDefault(); (l[i + 1] || l[0] || input).focus(); }
    else if (e.key === 'ArrowUp') { e.preventDefault(); (i > 0 ? l[i - 1] : input).focus(); }
  });

  start();
})();
</script>
