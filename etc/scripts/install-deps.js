#!/usr/bin/env node

const { project, InstallAsioOperation, InstallCrowOp } = require('./lib')

// ================================================
class Operation {
	async run() {
		project.ensureDirs()

		const asioOp = new InstallAsioOperation()
		await asioOp.install()

		const crowOp = new InstallCrowOp()
		await crowOp.install()
	}
}

// ================================================
const op = new Operation()
op.run()
