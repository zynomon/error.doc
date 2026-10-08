(function () {
  'use strict';
  var ED = window.ED, C = ED.cfg, root = document.documentElement;

  var CSS =
    'code,pre{border:1px solid color-mix(in srgb,currentColor 25%,transparent);border-radius:.4rem}' +
    'code{padding:.1em .4em}pre code{display:block;border:0;padding:0}' +
    '.code-block-wrapper{position:relative;margin:1rem 0}' +
    '.code-block-wrapper pre{margin:0;padding:.75rem 4.5rem .75rem .75rem;overflow-x:auto}' +
    '.copy-button{position:absolute;top:.4rem;right:.4rem;opacity:0;cursor:pointer;background:none;border:none;color:inherit;font-size:0.85rem}' +
    '.code-block-wrapper:hover .copy-button,.copy-button:focus-visible{opacity:1}' +
    '@media (hover:none){.copy-button{opacity:1}}' +
    'blockquote.note{--c:#2196f3}blockquote.tip{--c:#2ea043}blockquote.warning{--c:#e08a00}' +
    'blockquote.important{--c:#9b59b6}blockquote.caution,blockquote.danger{--c:#e5484d}' +
    'blockquote.note,blockquote.tip,blockquote.warning,blockquote.important,blockquote.caution,blockquote.danger' +
    '{background:linear-gradient(to right,color-mix(in srgb,var(--c) 30%,transparent),transparent)}' +
    'blockquote .title{display:inline-flex;align-items:center;gap:.4em;font-weight:bold}' +
    'blockquote .title svg{color:var(--c)}' +
    'header details summary h1{margin:0;padding:0;font-size:34px;line-height:1}' +
    'header details summary h1 a{display:block;color:inherit;text-decoration:none}';

  var svg = function (d) {
    return '<svg xmlns="http://www.w3.org/2000/svg" width="1em" height="1em" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">' + d + '</svg>';
  };
  var ICONS = {
    note:      svg('<path d="M9 5h11M9 12h11M9 19h11M4 5l1 1 2-2M4 12l1 1 2-2M4 19l1 1 2-2"/>'),
    tip:       svg('<path d="M9 18h6M10 21h4M12 3a6 6 0 0 0-3.5 10.9c.3.3.5.7.5 1.1v1h6v-1c0-.4.2-.8.5-1.1A6 6 0 0 0 12 3z"/>'),
    warning:   svg('<path d="M12 3l9 17H3z"/><path d="M12 10v4M12 17v.01"/>'),
    important: svg('<circle cx="12" cy="12" r="9"/><path d="M12 7v6M12 16.5v.01"/>'),
    caution:   svg('<path d="M8 3h8l5 5v8l-5 5H8l-5-5V8z"/><path d="M12 8v5M12 16v.01"/>'),
    danger:    svg('<circle cx="12" cy="12" r="9"/><path d="M15 9l-6 6M9 9l6 6"/>')
  };

  var HEADER =
    '<header><details>' +
    '<summary style="display:flex;align-items:center;list-style:none;cursor:pointer;user-select:none;-webkit-user-select:none;">' +
    '<img src="' + C.favicon + '" height="34" alt="">' +
    '<h1><a href="' + C.home + '">error.doc</a></h1>' +
    '<span style="margin-left:auto;" aria-hidden="true">●●●</span></summary>' +
    '<span id="links"></span><button type="button" id="settings-btn"><svg width="1em" height="1em" viewBox="0 0 100 100"><polygon points="50,0 100,25 100,75 50,100 0,75 0,25" fill="currentColor"/></svg> settings</button>' +
    '</details><hr></header>';

  var FOOTER =
    '<hr><footer><h2 style="font-family:\'Courier New\',\'Nimbus Mono PS\',monospace">error.os™</h2><div><div>' +
    '<a href="https://zynomon.github.io/error" aria-label="error"><img src="https://img.shields.io/badge/-%23121011.svg?logo=github&logoColor=white" alt="error"></a> ' +
    '<a href="https://discord.gg/Jn7FBwu99F" aria-label="Discord"><img src="https://img.shields.io/badge/-%235865F2.svg?&logo=discord&logoColor=white" alt="Discord"></a> ' +
    '<a href="https://zynomon.github.io/error/e.html" aria-label="Repository"><img src="https://img.shields.io/badge/-A81D33?logo=linux&logoColor=fff" alt="Repository"></a>' +
    '</div><h6>"born from failure, built for control." - Apache 2.0 Licensed, since 2025.</h6></footer>';

  var style = document.createElement('style');
  style.id = 'half-css';
  style.textContent = CSS;
  document.head.appendChild(style);

  var main = document.querySelector('main');
  main.insertAdjacentHTML('beforebegin', HEADER);
  main.insertAdjacentHTML('afterend', FOOTER);

  ED.links(document.getElementById('links'), function (l) {
    var b = document.createElement('button');
    b.type = 'button';
    if (l.name === 'search') b.insertAdjacentHTML('beforeend', '<svg width="1em" height="1em"><title>search</title><use href="#i-search"/></svg>');
    else if (l.icon) { var i = document.createElement('img'); i.src = l.icon; i.alt = ''; i.height = 16; b.appendChild(i); }
    b.appendChild(document.createTextNode(' ' + l.label));
    b.addEventListener('click', function () {
      if (ED.external(l.href)) window.open(l.href, '_blank', 'noopener'); else location.href = l.href;
    });
    return b;
  });
  
  ED.copy({ label: 'copy', done: 'copied' });
  ED.callouts(ICONS);
  
  var settingsDlg = document.getElementById('settings');
  var settingsBtn = document.getElementById('settings-btn');
  if (settingsDlg && settingsBtn) {
    ED.dialog(settingsDlg, [settingsBtn]);
  }

  root.classList.remove('pending');
})();
