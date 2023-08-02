#!/usr/bin/env node

const { CppBuild } = require('@almadash/builder')
const {
	errorHandler: { NodeErrorHandler },
	logger: { simpleLogger: logger },
} = require('@almadash/shelf')

const { project } = require('./lib')

// ================================================
class Operation {
	createOp() {
		const { cppVersion } = project
		const { rootDir, srcDir, buildDir } = project.paths

		const config = new CppBuild.Config()
			.version(cppVersion)
			.rootDir(rootDir)
			.entrypoint(`${srcDir}/main.cpp`)
			.output(`${buildDir}/app`)

		const op = new CppBuild({ config })

		// SDL2
		config.addInclude('/usr/local/include')
		op.cmdBuilder.addParam('L', '/usr/local/lib')
		op.cmdBuilder.addParam('l', 'SDL2')

		return op
	}

	// ================================================
	async buildApp() {
		logger.logHeader('build app')

		const buildOp = this.createOp()
		await buildOp.build()
	}

	// ================================================
	async buildTestStr() {
		const { srcDir } = project.paths

		logger.logHeader('running test <str>')

		const buildOp = this.createOp()
		buildOp.config.entrypoint(`${srcDir}/test/testStr.cpp`)

		await buildOp.build()
	}

	// ================================================
	async run() {
		const errorHandler = new NodeErrorHandler({ rootDir: `${__dirname}/..` })
		errorHandler.register()

		project.ensureDirs()

		const useTest = false

		if (useTest) {
			await this.buildTestStr()
		}
		else {
			await this.buildApp()
		}

		process.exit(0)
	}
}

// ================================================
const op = new Operation()
op.run()
