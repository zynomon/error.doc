---
layout: default
title: "Search"
description: "Search across every page of the error.os documentation"
---

# Search

<div id="search-app" data-site="{{ '/' | absolute_url }}" data-repo="zynomon/error.doc" data-branch="main" data-dir="docs/">
  <input class="s-input" id="s-input" type="search" placeholder="search across all docs" autocomplete="off" aria-label="Search all docs" disabled>
  <div class="s-load" id="s-load">
    <p class="s-status" id="s-status">loading docs .. 0/0</p>
    <div class="s-bar"><span id="s-bar"></span></div>
  </div>
  <p class="s-count" id="s-count"></p>
  <div id="s-results"></div>
</div>

<script>
(function () {
  var app = document.getElementById('search-app'), input = document.getElementById('s-input');
  var status = document.getElementById('s-status'), bar = document.getElementById('s-bar');
  var count = document.getElementById('s-count'), out = document.getElementById('s-results');
  var repo = app.dataset.repo, branch = app.dataset.branch, dir = app.dataset.dir, site = app.dataset.site;
  var RAW = 'https://raw.githubusercontent.com/' + repo + '/' + branch + '/';
  var link = document.querySelector('link[rel~="icon"]');
  var fallbackIcon = link ? link.href : '';
  var index = [], files = 0, done = 0, failed = 0, total = 0;

  var esc = function (s) { return s.replace(/[&<>"]/g, function (c) { return { '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]; }); };
  var rx  = function (s) { return s.replace(/[.*+?^$()|[\]\\{}]/g, '\\$&'); };
  var slug = function (t) { return t.toLowerCase().replace(/[^a-z0-9 -]/g, '').replace(/ /g, '-').replace(/^[^a-z]+/, ''); };

  /* every .md under docs/ : the git tree first, jsdelivr as the fallback when the api is rate limited */
  function list() {
    return fetch('https:
      .then(function (r) { if (!r.ok) throw 0; return r.json(); })
      .then(function (t) { return t.tree.map(function (f) { return f.path; }); })
      .catch(function () {
        return fetch('https://data.jsdelivr.com/v1/package/gh/' + repo + '@' + branch + '/flat')
          .then(function (r) { if (!r.ok) throw 0; return r.json(); })
          .then(function (d) { return d.files.map(function (f) { return f.name.replace(/^\
      })
      .then(function (all) { return all.filter(function (p) { return p.indexOf(dir) === 0 && /\.md$/i.test(p); }); });
  }

  var LIQUID = new RegExp('\\x7b[\\x7b%][\\s\\S]*?[\\x7d%]\\x7d', 'g');
  function clean(l) {
    return l.replace(/<[^>]*>/g, ' ').replace(LIQUID, ' ').replace(/\{:[^}]*\}/g, ' ')
      .replace(/!\[([^\]]*)\]\([^)]*\)/g, '$1').replace(/\[([^\]]*)\]\([^)]*\)/g, '$1')
      .replace(/^\s*>\s*(\[![A-Z]+\])?/, '').replace(/^\s*([-*+]|\d+\.)\s+/, '').replace(/[`*_|~]/g, ' ');
  }
  function parse(path, md) {
    var meta = {}, fm = md.match(/^---\r?\n([\s\S]*?)\r?\n---\r?\n?/);
    if (fm) {
      fm[1].split(/\r?\n/).forEach(function (l) { var m = l.match(/^([\w-]+):\s*["']?(.*?)["']?\s*$/); if (m) meta[m[1]] = m[2]; });
      md = md.slice(fm[0].length);
    }
    var id = path.replace(/\.md$/i, '').replace(/\/index$/i, '');
    var url = site + (meta.permalink ? meta.permalink.replace(/^\//, '') : /(^|\/)index\.md$/i.test(path) ? path.replace(/index\.md$/i, '') : path.replace(/\.md$/i, '.html'));
    var icon = meta.icon || fallbackIcon;
    var sec = { h: meta.title || id, a: '', t: [] }, seen = false, fence = false;
    function flush() {
      var t = sec.t.join(' ').replace(/\s+/g, ' ').trim();
      if (t || sec.a) index.push({ id: id + (sec.a ? '#' + sec.a : ''), url: url + (sec.a ? '#' + sec.a : ''), icon: icon, text: t, hl: sec.h.toLowerCase(), tl: t.toLowerCase() });
    }
    md.split(/\r?\n/).forEach(function (l) {
      if (/^\s*(```|~~~)/.test(l)) { fence = !fence; return; }
      var h = !fence && l.match(/^#{1,6}\s+(.+?)\s*#*\s*$/);
      if (h) {
        var ial = h[1].match(/\s*\{#([\w-]+)\}\s*$/), text = clean(h[1].replace(/\s*\{#[\w-]+\}\s*$/, '')).trim();
        var a = ial ? ial[1] : slug(text);
        if (!seen && !meta.title && !sec.t.length) { sec.h = text; sec.a = a; } else { flush(); sec = { h: text, a: a, t: [] }; }
        seen = true;
      } else if (!/^\s*[-*+]\s+\[[^\]]*\]\(#[^)]*\)\s*$/.test(l) && !/^\s*\|?[\s:|-]+\|?\s*$/.test(l)) sec.t.push(fence ? l : clean(l));
    });
    flush(); files++;
  }

  function progress() {
    status.textContent = 'loading docs .. ' + done + '/' + total;
    bar.style.width = (total ? done / total * 100 : 100) + '%';
  }
  function load(path) {
    return fetch(RAW + path.split('/').map(encodeURIComponent).join('/'))
      .then(function (r) { if (!r.ok) throw 0; return r.text(); })
      .then(function (md) { parse(path, md); })
      .catch(function () { failed++; })
      .then(function () { done++; progress(); });
  }

  /* everything is in memory now, so results are instant */
  function run() {
    var q = input.value.trim(), words = q.toLowerCase().split(/\s+/).filter(Boolean);
    history.replaceState(null, '', q ? '?q=' + encodeURIComponent(q) : location.pathname);
    if (!words.length) { count.textContent = index.length + ' sections in ' + files + ' docs'; out.innerHTML = ''; return; }
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
    count.textContent = hits.length ? hits.length + ' found' : 'nothing found';
    var re = new RegExp('(' + words.map(rx).join('|') + ')', 'i');
    out.innerHTML = hits.slice(0, 60).map(function (h) {
      var e = h.e, p = e.tl.indexOf(words[0]), from = Math.max(0, p < 0 ? 0 : p - 40);
      var snip = (from ? '…' : '') + e.text.slice(from, from + 140) + (from + 140 < e.text.length ? '…' : '');
      var mark = snip.split(re).map(function (v, i) { return i % 2 ? '<mark>' + esc(v) + '</mark>' : esc(v); }).join('');
      return '<a class="sr" href="' + esc(e.url) + '"><img src="' + esc(e.icon) + '" alt=""><b>' + esc(e.id) + '</b>:<span>' + mark + '</span></a>';
    }).join('');
  }

  input.addEventListener('input', run);
  app.addEventListener('keydown', function (e) {
    var l = [].slice.call(out.children), i = l.indexOf(document.activeElement);
    if (e.key === 'ArrowDown') { e.preventDefault(); (l[i + 1] || l[0] || input).focus(); }
    else if (e.key === 'ArrowUp') { e.preventDefault(); (i > 0 ? l[i - 1] : input).focus(); }
    else if (e.key === 'Enter' && document.activeElement === input && l[0]) l[0].click();
  });

  progress();
  list().then(function (paths) {
    total = paths.length; progress();
    return Promise.all(paths.map(load));
  }).catch(function () { total = 0; }).then(function () {
    document.getElementById('s-load').hidden = true;
    if (!files) { count.textContent = 'could not load the docs from github'; return; }
    input.disabled = false; input.focus();
    var q = new URLSearchParams(location.search).get('q'); if (q) input.value = q;
    run();
    if (failed) count.textContent += ' ( ' + failed + ' failed to load )';
  });
})();
</script>
