#!/usr/bin/env node

const { CppBuild } = require('@almadash/builder')
const {
	errorHandler: { NodeErrorHandler },
	logger: { simpleLogger: logger },
	BusinessException,
} = require('@almadash/shelf')
const { dep, fsShelf } = require('@almadash/shelf-node')

const { project } = require('./lib')

// ================================================
class Operation {
	createOp(options) {
		const { cppVersion } = project
		const { rootDir, srcDir, buildDir, frameworksDir } = project.paths

		let useSdl = false
		let useSdlTtf = false

		if (options) {
			useSdl = options.useSdl
			useSdlTtf = options.useSdlTtf
		}
		else {
			useSdl = true
			useSdlTtf = true
		}

		const config = new CppBuild.Config()
			.version(cppVersion)
			.rootDir(rootDir)
			.entrypoint(`${srcDir}/main.cpp`)
			.output(`${buildDir}/app`)

		const op = new CppBuild({ config })

		if (useSdl) {
			// SDL2
			config.addInclude('/usr/local/include')
			op.cmdBuilder.addParam('L', '/usr/local/lib')
			op.cmdBuilder.addParam('l', 'SDL2')
		}

		if (useSdlTtf) {
			// SDL2_ttf
			const sdlTtf = `${frameworksDir}/SDL2_ttf.framework`
			config.addInclude(`${sdlTtf}/Versions/A/Headers`)
			op.cmdBuilder.addParam('F', sdlTtf)
			op.cmdBuilder.addParam('framework', 'SDL2_ttf')
		}

		return op
	}

	// ================================================
	async buildApp() {
		logger.logHeader('build app')

		const buildOp = this.createOp()
		await buildOp.build()
	}

	async testCompile() {
		logger.logHeader('test compile')

		const buildOp = this.createOp().verbose()
		await buildOp.dry()
	}

	// ================================================
	async buildTest(testName) {
		const { testDir } = project.paths

		const testFile = `${testDir}/${testName}.cpp`
		if (!fsShelf.exists(testFile)) {
			throw new BusinessException(`test NOT found: ${testName}`)
		}

		let buildOp = this.createOp()
		if (testName === 'test-sdl') {
			buildOp = this.createOp({ useSdl: true })
		}
		if (testName === 'test-sdl-ttf') {
			buildOp = this.createOp({ useSdl: true, useSdlTtf: true })
		}

		buildOp.config.entrypoint(testFile)

		await buildOp.build()
	}

	// ================================================
	async run() {
		const errorHandler = new NodeErrorHandler({ rootDir: `${__dirname}/..` })
		errorHandler.register()

		project.ensureDirs()

		let data = { entry: 'main' }
		dep.whenAvailable(`${__dirname}/config.local.js`, localConfig => {
			logger.logHeader('local config FOUND')
			data = localConfig
		})

		const { entry } = data

		if (entry === 'main') {
			await this.buildApp()
		}
		else if (entry === 'testCompile') {
			await this.testCompile()
		}
		else if (entry === 'test') {
			const { testName = 'sdl' } = data
			logger.logHeader(`building test: '${testName}'`)
			await this.buildTest(testName)
		}

		logger.logHeader('build complete')

		process.exit(0)
	}
}

// ================================================
const op = new Operation()
op.run()
