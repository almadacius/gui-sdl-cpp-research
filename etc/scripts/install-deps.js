#!/usr/bin/env node

const { errorHandler: { NodeErrorHandler } } = require('@almadash/shelf')

const { project, InstallSdlTtfOp } = require('./lib')

// ================================================
class Operation {
	async run() {
		const errorHandler = new NodeErrorHandler({
			rootDir: `${__dirname}/../..`,
		})
		errorHandler.register()

		project.ensureDirs()

		const sdlTtfOp = new InstallSdlTtfOp()
		await sdlTtfOp.install()
	}
}

// ================================================
const op = new Operation()
op.run()
