#!/usr/bin/env node

const { CppBuild, CppBuild2 } = require('@almadash/builder')
const {
	errorHandler: { NodeErrorHandler },
	logger: { simpleLogger: logger },
} = require('@almadash/shelf')

const { project } = require('./lib')

// ================================================
class Operation {
	async buildProjectLegacy() {
		const { cppVersion } = project
		const { srcDir, rootDir, buildDir, modulesDir } = project.paths

		const buildOp = new CppBuild({
			baseDir: rootDir,
			// baseDir: srcDir,
			version: cppVersion,
			srcDir,
			output: `${buildDir}/server`,
			includes: [
				srcDir,
				modulesDir,
			],
			// modulesDir: `${rootDir}/temp/local_modules`,
		})
		await buildOp.build()
	}

	// ================================================
	getBaseConfig() {
		const { cppVersion } = project
		const { rootDir, srcDir, buildDir, modulesDir } = project.paths

		return {
			version: cppVersion,
			entrypoint: `${srcDir}/main.cpp`,
			output: `${buildDir}/server`,

			baseDir: rootDir,
			srcDir,
			headerDir: srcDir,
			includes: [
				modulesDir,
			],
		}
	}

	// ================================================
	async buildServer() {
		const { srcDir } = project.paths

		logger.logHeader('running main')

		const config = this.getBaseConfig()
		const buildOp = new CppBuild2({
			...config,
			entrypoint: `${srcDir}/main.cpp`,
		})
		await buildOp.build()
	}

	// ================================================
	async buildTestStr() {
		const { srcDir } = project.paths

		logger.logHeader('running test <str>')

		const config = this.getBaseConfig()
		const buildOp = new CppBuild2({
			...config,
			entrypoint: `${srcDir}/test/testStr.cpp`,
		})
		await buildOp.build()
	}

	async buildTestFs() {
		const { srcDir } = project.paths

		logger.logHeader('running test <fs>')

		const config = this.getBaseConfig()
		const buildOp = new CppBuild2({
			...config,
			entrypoint: `${srcDir}/test/testFs.cpp`,
		})
		await buildOp.build()
	}

	// ================================================
	async run() {
		const errorHandler = new NodeErrorHandler({ rootDir: `${__dirname}/..` })
		errorHandler.register()

		project.ensureDirs()

		const useTest = false

		if (useTest) {
			// await this.buildProjectLegacy()
			// await this.buildTestStr()
			await this.buildTestFs()
		}
		else {
			await this.buildServer()
		}

		process.exit(0)
	}
}

// ================================================
const op = new Operation()
op.run()
