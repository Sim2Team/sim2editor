/*
	This implementation is based of Pk11's theme.js, however reworked in my style. ;P

	https://github.com/Epicpkmn11/pk11.us/blob/master/assets/js/theme.js

	Credits goes to Pk11 for it!
*/

/* Loads a theme. */
function LoadTheme() {
	const CurTheme = document.getElementById("themeCSS");

	if (!localStorage.theme || localStorage.theme == "default") {
		if (CurTheme) CurTheme.remove();

	} else {
		if (CurTheme) CurTheme.href = "./assets/css/" + localStorage.theme + ".css";
		else {
			const Link = document.createElement("link");
			Link.rel = "stylesheet";
			Link.href = "./assets/css/" + localStorage.theme + ".css"
			Link.id = "themeCSS";

			document.head.appendChild(Link);
		}
	}
};

/* Sets a theme. */
function SetTheme(Theme) {
	if (Theme == "default") delete localStorage.theme;
	else localStorage.theme = Theme;

	LoadTheme();
};

LoadTheme();