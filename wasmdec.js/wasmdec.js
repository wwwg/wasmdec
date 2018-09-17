(() => {
	class Decompiler {
		constructor(enableDebugLogging, emitExtraInfo,
			inputType, input) {
				this._ptr = Wasmdec._wasmdec_create_decompiler(enableDebugLogging, emitExtraInfo,
					inputType, input);
			}
			decompile() {
				return Wasmdec._wasmdec_decompile(this._ptr);
			}
			getDecompiledCode() {
				return Wasmdec._wasmdec_get_decompiled_code(this._ptr);
			}
			destroy() {
				// MUST be called to free wasm memory
				Wasmdec._wasmdec_destroy_decompiler(this._ptr);
			}
	}
	window.Wasmdec = {
		ready: false,
		onReady: null,
		Decompiler: Decompiler
	};
	let glue = document.createElement('script');
	glue.src = 'https://rawgit.com/wwwg/wasmdec/master/wasmdec.js/wasmdec.wasm.js';
	document.head.appendChild(glue);
	glue.onload = () => {
		let intv = setInterval(() => {
			if (Wasmdec.Module["_wasmdec_create_decompiler"]) {
				clearInterval(intv);
				if (!Wasmdec.ready) {
					init();
				} else {
					if (Wasmdec.onReady) {
						Wasmdec.onReady();
					}
					clearInterval(intv);
				}
				return;
			}
		});
	}
	let init = () => {
		Wasmdec.ready = true;
		// bind wasm functions to javascript
		Wasmdec._wasmdec_create_decompiler = Wasmdec.Module.cwrap('wasmdec_create_decompiler', 'number',
                                                                                                    ['bool', 'bool', 'string', 'string']);
		Wasmdec._wasmdec_decompile = Wasmdec.Module.cwrap('wasmdec_decompile', 'bool', ['number']);
		Wasmdec._wasmdec_get_decompiled_code = Wasmdec.Module.cwrap('wasmdec_get_decompiled_code', 'string', ['number']);
		Wasmdec._wasmdec_destroy_decompiler = Wasmdec.Module.cwrap('wasmdec_destroy_decompiler', 'void', ['number']);
	}
})();