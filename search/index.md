---
layout: default
title: "Search"
description: "Search across every page of the error.os documentation"
---

# Search

<div id="search-app" data-base="{{ '/' | relative_url }}" data-pages="{{ search_pages | jsonify | escape }}">
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
  var app     = document.getElementById('search-app');
  var input   = document.getElementById('s-input');
  var loading = document.getElementById('s-load');
  var status  = document.getElementById('s-status');
  var bar     = document.getElementById('s-bar');
  var count   = document.getElementById('s-count');
  var out     = document.getElementById('s-results');

  var base  = app.dataset.base.replace(/\/$/, '');
  var urls  = JSON.parse(app.dataset.pages);
  var index = [];
  var done  = 0, failed = 0, pages = 0;

  var esc   = function (s) { return s.replace(/[&<>"]/g, function (c) { return { '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]; }); };
  var regex = function (s) { return s.replace(/[.*+?^$()|[\]\\{}]/g, '\\$&'); };

  function parse(html, url) {
    var doc  = new DOMParser().parseFromString(html, 'text/html');
    var main = doc.querySelector('main');
    if (!main) return;
    var link = doc.querySelector('link[rel~="icon"]');
    var icon = link ? new URL(link.getAttribute('href'), location.href).href : '';
    var id   = url.replace(/^\/|\/$/g, '') || 'home';

    main.querySelectorAll('script, style, nav, .copy-button').forEach(function (n) { n.remove(); });
    main.querySelectorAll('ul, ol').forEach(function (l) {
      var a = l.querySelectorAll('a');
      if (a.length && a.length === l.querySelectorAll('li').length &&
          [].every.call(a, function (x) { return (x.getAttribute('href') || '').charAt(0) === '#'; })) l.remove();
    });

    var sec = { h: doc.title.replace(/^error\.doc\s*›\s*/, '') || id, a: '', t: [] };
    var seen = false;
    function flush() {
      var t = sec.t.join(' ').replace(/\s+/g, ' ').trim();
      if (!t && !sec.a) return;
      index.push({ id: id + (sec.a ? '#' + sec.a : ''), url: base + url + (sec.a ? '#' + sec.a : ''), icon: icon,
                   text: t, hl: sec.h.toLowerCase(), tl: t.toLowerCase() });
    }
    var BLOCK = 'h1,h2,h3,h4,h5,h6,p,li,pre,td,th,blockquote,dt,dd,summary';
    main.querySelectorAll(BLOCK).forEach(function (e) {
      var text = e.textContent.trim();
      if (/^H\d$/.test(e.tagName)) {
        if (!seen && !sec.t.length) { sec.h = text; sec.a = e.id; }
        else { flush(); sec = { h: text, a: e.id, t: [] }; }
        seen = true;
      } else if (!e.querySelector(BLOCK)) sec.t.push(text);
    });
    flush();
    pages++;
  }

  function progress() {
    status.textContent = 'loading docs .. ' + done + '/' + urls.length;
    bar.style.width = (urls.length ? done / urls.length * 100 : 100) + '%';
  }

  function load(url) {
    return fetch(base + url).then(function (r) { if (!r.ok) throw r.status; return r.text(); })
      .then(function (html) { parse(html, url); })
      .catch(function () { failed++; })
      .then(function () { done++; progress(); });
  }

  function run() {
    var q = input.value.trim().toLowerCase();
    history.replaceState(null, '', q ? '?q=' + encodeURIComponent(input.value.trim()) : location.pathname);
    var words = q.split(/\s+/).filter(Boolean);
    if (!words.length) { count.textContent = index.length + ' sections in ' + pages + ' docs'; out.innerHTML = ''; return; }

    var hits = [];
    index.forEach(function (e, n) {
      var score = 0;
      for (var i = 0; i < words.length; i++) {
        var h = e.hl.indexOf(words[i]) > -1, t = e.tl.indexOf(words[i]) > -1;
        if (!h && !t) return;
        score += (h ? 5 : 0) + (t ? 1 : 0);
      }
      hits.push({ e: e, s: score, n: n });
    });
    hits.sort(function (a, b) { return b.s - a.s || a.n - b.n; });
    count.textContent = hits.length ? hits.length + ' found' : 'nothing found';

    var re = new RegExp('(' + words.map(regex).join('|') + ')', 'i');
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
  Promise.all(urls.map(load)).then(function () {
    loading.hidden = true;
    input.disabled = false;
    input.focus();
    if (!pages) { count.textContent = 'could not load the docs'; return; }
    var q = new URLSearchParams(location.search).get('q');
    if (q) input.value = q;
    run();
    if (failed) count.textContent += ' ( ' + failed + ' page' + (failed > 1 ? 's' : '') + ' failed to load )';
  });
})();
</script>
