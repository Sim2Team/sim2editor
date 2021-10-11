---
---

const BaseUrl = "{{ "/" | absolute_url }}";

/* Loads a theme. */
function LoadTheme() {
    if (!localStorage.theme || localStorage.theme == "default") localStorage.theme = "green"; // Set to default theme - green.
    document.getElementById("themeCSS").href = BaseUrl + "assets/css/" + localStorage.theme + ".css";
};

/* Sets a theme. */
function SetTheme(Theme) {
	localStorage.theme = Theme;
	LoadTheme();
};

LoadTheme();