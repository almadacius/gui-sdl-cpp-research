#!/usr/bin/env node

const { errorHandler: { NodeErrorHandler } } = require('@almadash/shelf')

const { project, InstallSdlTtfOp, InstallSdlOp } = require('./lib')

// ================================================
class Operation {
	async run() {
		const errorHandler = new NodeErrorHandler({
			rootDir: `${__dirname}/../..`,
		})
		errorHandler.register()

		project.ensureDirs()

		const promises = []

		promises.push(async () => {
			const op = new InstallSdlOp()
			await op.install()
		})

		promises.push(async () => {
			const op = new InstallSdlTtfOp()
			await op.install()
		})

		await Promise.all(promises.map(p => p()))
	}
}

// ================================================
const op = new Operation()
op.run()
