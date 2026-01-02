// Wait for the DOM to be fully loaded before running the script
document.addEventListener('DOMContentLoaded', main);

/**
 * Main function to initialize the application.
 */
async function main() {
    buildUI();

    const docIds = await getDocumentIds();
    if (!docIds) {
        console.error("Failed to load document manifest. Site may not function correctly.");
        return;
    }

    const currentDocId = detectId();
    if (currentDocId) {
        loadContent(currentDocId);
    }

    setupEventListeners();
    populateSideMenu(docIds);
    buildSearchIndex(docIds);
}


/**
 * Fetches the list of document IDs from the manifest file.
 * @returns {Promise<string[]|null>} A promise that resolves to an array of IDs.
 */
async function getDocumentIds() {
    try {
        const response = await fetch('../manifest.json');
        if (!response.ok) {
            throw new Error(`Network response was not ok: ${response.statusText}`);
        }
        const data = await response.json();
        return data.documents;
    } catch (error) {
        console.error("Error fetching or parsing manifest.json:", error);
        return null;
    }
}

/**
 * Creates the main HTML structure for the new design and injects it into the body.
 */
function buildUI() {
    const body = document.body;
    body.innerHTML = ''; // Clear existing body content

    const sideMenu = document.createElement('nav');
    sideMenu.id = 'side-menu';
    sideMenu.className = 'glass';

    const header = document.createElement('header');
    header.className = 'navbar glass';

    const mainContent = document.createElement('main');

    const contentArea = document.createElement('div');
    contentArea.id = 'content-area';
    contentArea.className = 'glass';
    mainContent.appendChild(contentArea);

    const footer = document.createElement('footer');
    footer.className = 'glass';

    header.innerHTML = `
        <button class="hamburger-btn" id="hamburger-btn">
            <span></span>
            <span></span>
            <span></span>
        </button>
        <div class="url-breadcrumb" id="url-breadcrumb">
            error.doc / docs / <strong>...</strong>
        </div>
        <div class="search-container">
            <input type="search" id="search-input" class="search-input" placeholder="Search docs...">
            <div id="search-results" class="search-results-container"></div>
        </div>
    `;

    sideMenu.innerHTML = `
        <h2 id="side-menu-title">Navigation</h2>
        <ul id="side-menu-content">
            <!-- Links will be populated here -->
        </ul>
    `;

    footer.innerHTML = `
        <a href="#" target="_blank">Discord</a>
        <a href="#" target="_blank">GitHub</a>
    `;

    body.appendChild(sideMenu);
    body.appendChild(header);
    body.appendChild(mainContent);
    body.appendChild(footer);
}

/**
 * Detects the document ID from the current URL path.
 */
function detectId() {
    const pathParts = window.location.pathname.split('/');
    if (pathParts.length > 2) {
        const potentialId = pathParts[pathParts.length - 2];
        if (!isNaN(parseInt(potentialId))) {
            return potentialId;
        }
    }
    return null;
}

/**
 * Fetches, parses, and renders the content of a CXML file.
 */
async function loadContent(id) {
    const contentArea = document.getElementById('content-area');
    const breadcrumb = document.getElementById('url-breadcrumb');
    const url = `${id}.xml`;

    try {
        const response = await fetch(url);
        if (!response.ok) throw new Error(`Failed to fetch: ${response.statusText}`);

        const xmlText = await response.text();
        const parser = new DOMParser();
        const xmlDoc = parser.parseFromString(xmlText, "application/xml");

        if (xmlDoc.getElementsByTagName("parsererror").length) {
            throw new Error("Failed to parse XML.");
        }

        breadcrumb.innerHTML = `error.doc / docs / <strong>${id}</strong>`;
        renderDocumentation(xmlDoc, contentArea);

    } catch (error) {
        console.error('Failed to load document content:', error);
        contentArea.innerHTML = `<div class="warning">${error.message}</div>`;
    }
}

/**
 * Renders the parsed XML document into the content area.
 */
function renderDocumentation(xmlDoc, contentArea) {
    const title = xmlDoc.querySelector('title')?.textContent || 'Untitled';
    const icon = xmlDoc.querySelector('icon')?.textContent;
    const preview = xmlDoc.querySelector('preview')?.textContent;
    const contentNode = xmlDoc.querySelector('content');

    document.title = title;

    let contentHtml = '';
    if (preview) {
        contentHtml += `<img src="${preview}" alt="Preview Banner" class="preview-banner">`;
    }

    contentHtml += `<div class="title-header">`;
    if (icon) {
        contentHtml += `<img src="${icon}" alt="Icon" class="doc-icon">`;
    }
    contentHtml += `<h1 class="doc-title">${title}</h1></div>`;

    if (contentNode) {
        contentHtml += `<div class="content-body">`;
        contentNode.childNodes.forEach(node => {
            if (node.nodeType !== 1) return;

            switch (node.tagName.toLowerCase()) {
                case 'p':
                    contentHtml += `<p>${node.textContent}</p>`;
                    break;
                case 'warning':
                    contentHtml += `<div class="warning">${node.textContent}</div>`;
                    break;
                case 'code':
                    const type = node.getAttribute('type') || '';
                    contentHtml += `<div class="code-block" data-type="${type}"><pre><code>${node.textContent.trim()}</code></pre></div>`;
                    break;
                case 'embed':
                    if (node.getAttribute('type') === 'link') {
                        const href = node.getAttribute('href');
                        contentHtml += `<a href="${href}" target="_blank" class="embedded-link">🔗 ${href}</a>`;
                    }
                    break;
                case 'hr':
                    contentHtml += `<hr style="border-color: var(--border-color); margin: 2rem 0;">`;
                    break;
            }
        });
        contentHtml += `</div>`;
    }

    contentArea.innerHTML = contentHtml;
}

/**
 * Sets up global event listeners for UI elements.
 */
function setupEventListeners() {
    const hamburgerBtn = document.getElementById('hamburger-btn');
    const sideMenu = document.getElementById('side-menu');
    const searchInput = document.getElementById('search-input');

    if (hamburgerBtn && sideMenu) {
        hamburgerBtn.addEventListener('click', (e) => {
            e.stopPropagation();
            sideMenu.classList.toggle('open');
        });
    }

    document.addEventListener('click', (e) => {
        if (sideMenu && sideMenu.classList.contains('open') && !sideMenu.contains(e.target)) {
            sideMenu.classList.remove('open');
        }
    });

    if (searchInput) {
        searchInput.addEventListener('input', handleSearch);
    }
}

/**
 * Fetches the titles of all documents and populates the side navigation menu.
 */
async function populateSideMenu(docIds) {
    const menuContent = document.getElementById('side-menu-content');
    if (!menuContent || !docIds) return;
    let menuHtml = '';

    for (const id of docIds) {
        try {
            const response = await fetch(`../${id}/${id}.xml`);
            if (!response.ok) continue;

            const xmlText = await response.text();
            const parser = new DOMParser();
            const xmlDoc = parser.parseFromString(xmlText, "application/xml");

            const title = xmlDoc.querySelector('title')?.textContent || `Document ${id}`;
            const shortDesc = xmlDoc.querySelector('short')?.textContent || '';

            menuHtml += `
                <li>
                    <a href="../docs/${id}/">
                        <strong>${title}</strong>
                        <small style="display: block; color: var(--secondary-text);">${shortDesc}</small>
                    </a>
                </li>
            `;
        } catch (error) {
            console.error(`Failed to load menu item for doc ${id}:`, error);
        }
    }
    menuContent.innerHTML = menuHtml;
}

let searchIndex = [];

/**
 * Builds a searchable index from all documents listed in the manifest.
 */
async function buildSearchIndex(docIds) {
    if (!docIds) return;
    for (const id of docIds) {
        try {
            const response = await fetch(`../${id}/${id}.xml`);
            if (!response.ok) continue;

            const xmlText = await response.text();
            const parser = new DOMParser();
            const xmlDoc = parser.parseFromString(xmlText, "application/xml");

            const title = xmlDoc.querySelector('title')?.textContent || '';
            const short = xmlDoc.querySelector('short')?.textContent || '';
            const content = xmlDoc.querySelector('content')?.textContent || '';

            searchIndex.push({ id, title, short, content });
        } catch (error) {
            console.error(`Error building search index for doc ${id}:`, error);
        }
    }
}

/**
 * Creates a snippet of text around the first occurrence of a query.
 */
function createSnippet(text, query) {
    const index = text.toLowerCase().indexOf(query.toLowerCase());
    if (index === -1) {
        return text.substring(0, 100) + '...'; // Fallback snippet
    }
    const start = Math.max(0, index - 30);
    const end = Math.min(text.length, index + query.length + 30);
    let snippet = text.substring(start, end);

    // Highlight the query in the snippet
    snippet = snippet.replace(new RegExp(query, 'gi'), (match) => `<strong>${match}</strong>`);

    return (start > 0 ? '...' : '') + snippet + (end < text.length ? '...' : '');
}


/**
 * Handles the search input, filters the index, and displays results.
 */
function handleSearch(event) {
    const query = event.target.value.toLowerCase().trim();
    const searchResultsContainer = document.getElementById('search-results');

    if (!query) {
        searchResultsContainer.style.display = 'none';
        return;
    }

    const results = searchIndex.filter(doc => {
        return doc.title.toLowerCase().includes(query) ||
               doc.short.toLowerCase().includes(query) ||
               doc.content.toLowerCase().includes(query);
    }).map(doc => {
        // Create a snippet for each result
        const snippet = createSnippet(doc.content, query);
        return { ...doc, snippet };
    });

    displaySearchResults(results, query);
}

/**
 * Renders the search results into the dropdown.
 */
function displaySearchResults(results, query) {
    const searchResultsContainer = document.getElementById('search-results');
    let resultsHtml = '<ul>';

    if (results.length === 0) {
        resultsHtml += '<li class="no-results">No results found</li>';
    } else {
        results.forEach(doc => {
            resultsHtml += `
                <li>
                    <a href="../docs/${doc.id}/">
                        <div class="result-info">
                            <span class="result-title">${doc.title}</span>
                            <span class="result-id">ID: ${doc.id}</span>
                        </div>
                        <p class="result-snippet">${doc.snippet}</p>
                    </a>
                </li>
            `;
        });
    }

    resultsHtml += '</ul>';
    searchResultsContainer.innerHTML = resultsHtml;
    searchResultsContainer.style.display = 'block';
}
