(() => {
	window.Wasmdec = {};
	let glue = document.createElement('script');
	glue.src = 'https://rawgit.com/wwwg/wasmdec/master/wasmdec.js/wasmdec.wasm.js';
	document.head.appendChild(glue);
	glue.onload = () => {
		//
	}
})();