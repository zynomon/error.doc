// script.js — dynamic, local-only, no hardcoding
(function () {
  "use strict";

  // Get current doc ID from URL path
  function getCurrentId() {
    const match = window.location.pathname.match(/\/docs\/([0-9]{3})\//);
    return match ? match[1] : null;
  }

  // Fetch and parse XML
  async function loadXml(id) {
    const res = await fetch(`./${id}.xml`);
    if (!res.ok) throw new Error("XML not found");
    const text = await res.text();
    const parser = new DOMParser();
    const doc = parser.parseFromString(text, "application/xml");
    if (doc.querySelector("parsererror")) throw new Error("Invalid XML");

    const root = doc.documentElement;
    if (root.tagName !== "doc") throw new Error("Root must be <doc>");

    // Required fields
    const fields = ["id", "title", "icon", "preview", "short"].reduce(
      (acc, tag) => {
        const el = root.querySelector(tag);
        acc[tag] = el ? el.textContent.trim() : "";
        return acc;
      },
      {},
    );

    if (!fields.id || !fields.title || !fields.short)
      throw new Error("Missing required fields");
    if (fields.id !== id) throw new Error("ID mismatch");

    return { fields, content: root.querySelector("content") };
  }

  // Render XML content
  function renderContent(contentNode) {
    const div = document.createDocumentFragment();
    if (!contentNode) return div;

    Array.from(contentNode.children).forEach((node) => {
      if (node.nodeType !== Node.ELEMENT_NODE) return;
      let el;
      const tag = node.tagName.toLowerCase();
      const txt = node.textContent || "";

      switch (tag) {
        case "p":
          el = document.createElement("p");
          el.textContent = txt;
          break;
        case "warning":
          el = document.createElement("div");
          el.className = "alert alert-warning";
          el.textContent = txt;
          break;
        case "code":
          el = document.createElement("pre");
          el.className =
            "bg-gray-800 p-4 rounded my-4 overflow-x-auto relative";
          const code = document.createElement("code");
          code.textContent = txt;
          if (node.getAttribute("type") === "shell")
            code.className = "text-green-400";
          el.appendChild(code);
          // Copy button
          const btn = document.createElement("button");
          btn.className =
            "btn btn-xs btn-ghost absolute top-2 right-2 opacity-0 group-hover:opacity-100";
          btn.innerHTML = "📋";
          btn.onclick = () => navigator.clipboard.writeText(txt);
          el.className += " group";
          el.appendChild(btn);
          break;
        case "hr":
          el = document.createElement("hr");
          el.className = "my-6 border-gray-700";
          break;
        case "embed":
          const href = node.getAttribute("href")?.trim();
          if (href) {
            el = document.createElement("a");
            el.href = href;
            el.target = "_blank";
            el.rel = "noopener";
            el.className = "link link-info break-all";
            el.textContent = href;
          }
          break;
        default:
          el = document.createElement("p");
          el.innerHTML = `<code class="text-red-400">&lt;${tag}&gt;</code>: ${txt}`;
      }
      if (el) div.appendChild(el);
    });

    const wrapper = document.createElement("div");
    wrapper.appendChild(div);
    return wrapper;
  }

  // Discover valid docs by probing ../XXX/
  async function discoverDocs() {
    const docs = [];
    for (let i = 0; i <= 999; i++) {
      const id = i.toString().padStart(3, "0");
      try {
        // Check if index.html exists
        const res = await fetch(`../${id}/index.html`, { method: "HEAD" });
        if (res.ok) {
          // Check if XML exists and is valid
          const xmlRes = await fetch(`../${id}/${id}.xml`, { method: "HEAD" });
          if (xmlRes.ok) docs.push(id);
        }
      } catch (e) {
        // Skip silently
      }
    }
    return docs;
  }

  // Render sidebar
  async function renderSidebar() {
    const list = document.getElementById("topic-list");
    const ids = await discoverDocs();
    list.innerHTML = "";
    for (const id of ids) {
      try {
        const res = await fetch(`../${id}/${id}.xml`);
        const text = await res.text();
        const parser = new DOMParser();
        const doc = parser.parseFromString(text, "application/xml");
        const title = doc.querySelector("title")?.textContent?.trim() || id;
        const li = document.createElement("li");
        const a = document.createElement("a");
        a.href = `../${id}/`;
        a.className = "block py-1 px-2 hover:bg-gray-800 rounded";
        a.textContent = title;
        li.appendChild(a);
        list.appendChild(li);
      } catch (e) {
        // Skip invalid
      }
    }
  }

  // Render URL bar (GitHub-like)
  function renderUrlBar(id) {
    const bar = document.getElementById("url-bar");
    bar.innerHTML = "";
    const parts = [
      { text: "error.doc", href: "../../" },
      { text: "docs", href: "../" },
      { text: id, href: "./", current: true },
    ];
    parts.forEach((part, i) => {
      const span = document.createElement("span");
      if (part.href) {
        const a = document.createElement("a");
        a.href = part.href;
        a.className = part.current ? "text-red-400 font-bold" : "text-blue-400";
        a.textContent = part.text;
        span.appendChild(a);
      } else {
        span.textContent = part.text;
        if (part.current) span.className = "text-red-400 font-bold";
      }
      bar.appendChild(span);
      if (i < parts.length - 1) bar.appendChild(document.createTextNode(" / "));
    });
  }

  // Main boot
  async function boot() {
    const id = getCurrentId();
    if (!id) {
      document.getElementById("content").innerHTML =
        '<div class="alert alert-error">Invalid URL</div>';
      return;
    }

    try {
      const { fields, content } = await loadXml(id);

      // URL bar
      renderUrlBar(id);

      // Meta
      document.getElementById("doc-title").textContent = fields.title;
      document.getElementById("doc-id").textContent = `ID: ${fields.id}`;
      document.getElementById("doc-date").textContent = "Uploaded: —";
      document.getElementById("doc-author").textContent = "Uploader: —";
      document.getElementById("meta").classList.remove("hidden");

      // Preview
      if (fields.preview) {
        const img = document.createElement("img");
        img.src = fields.preview;
        img.className = "w-full h-full object-cover";
        document.getElementById("preview").innerHTML = "";
        document.getElementById("preview").appendChild(img);
        document.getElementById("preview").classList.remove("hidden");
      }

      // Content
      document.getElementById("content").innerHTML = "";
      document.getElementById("content").appendChild(renderContent(content));

      // Title
      document.title = `error.doc • ${fields.title}`;
    } catch (e) {
      document.getElementById("content").innerHTML =
        `<div class="alert alert-error">${e.message}</div>`;
    }
  }

  // Mobile menu
  function setupMobile() {
    const toggle = document.getElementById("menu-toggle");
    const close = document.getElementById("menu-close");
    const sidebar = document.getElementById("sidebar");
    const overlay = document.getElementById("overlay");

    const show = () => {
      sidebar.classList.remove("hidden");
      overlay.classList.remove("hidden");
    };
    const hide = () => {
      sidebar.classList.add("hidden");
      overlay.classList.add("hidden");
    };

    toggle?.addEventListener("click", show);
    close?.addEventListener("click", hide);
    overlay?.addEventListener("click", hide);
  }

  // Init
  boot();
  renderSidebar();
  setupMobile();
})();
