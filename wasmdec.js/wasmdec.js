(() => {
	window.Wasmdec = {
		ready: false
	};
	let glue = document.createElement('script');
	glue.src = 'https://rawgit.com/wwwg/wasmdec/master/wasmdec.js/wasmdec.wasm.js';
	document.head.appendChild(glue);
	glue.onload = () => {
		let intv = setInterval(() => {
			if (Wasmdec.Module["_wasmdec_create_decompiler"]) {
				init();
				clearInterval(intv);
				return;
			}
		});
	}
	let init = () => {
		Wasmdec.ready = true;
		// bind wasm functions to javascript
		Wasmdec._wasmdec_create_decompiler = Module.cwrap('wasmdec_create_decompiler', 'number',
                                                                                                    ['bool', 'bool', 'string', 'string']);
		Wasmdec._wasmdec_decompile = Module.cwrap('wasmdec_decompile', 'bool', ['number']);
		Wasmdec._wasmdec_get_decompiled_code = Module.cwrap('wasmdec_get_decompiled_code', 'string', ['number']);
		Wasmdec._wasmdec_destroy_decompiler = Module.cwrap('wasmdec_destroy_decompiler', 'void', ['number']);
	}
})();