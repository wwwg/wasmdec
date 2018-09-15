(() => {
	window.Wasmdec = {
		ready: false
	};
	let glue = document.createElement('script');
	glue.src = 'https://rawgit.com/wwwg/wasmdec/master/wasmdec.js/wasmdec.wasm.js';
	document.head.appendChild(glue);
	glue.onload = () => {
		let intv = setInterval(() => {
			if (Module["_wasmdec_create_decompiler"]) {
				init();
				clearInterval(intv);
				return;
			}
		});
	}
	let init = () => {
		Wasmdec.ready = true;
	}
})();