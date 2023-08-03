#!/usr/bin/env node

const { project, InstallSdlTtfOp } = require('./lib')

// ================================================
class Operation {
	async run() {
		project.ensureDirs()

		const sdlTtfOp = new InstallSdlTtfOp()
		await sdlTtfOp.install()
	}
}

// ================================================
const op = new Operation()
op.run()
