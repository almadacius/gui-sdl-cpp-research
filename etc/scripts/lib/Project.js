const nodePath = require('path')

const { obj } = require('@almadash/shelf')
const { fsShelf } = require('@almadash/shelf-node')

// ================================================
class Project {
	constructor() {
		const paths = obj.incrementObj(
			() => ({
				rootDir: nodePath.resolve(`${__dirname}/../../..`),
			}),
			paths => ({
				testDir: `${paths.rootDir}/_tests-unit`,
				srcDir: `${paths.rootDir}/src`,
				modulesDir: `${paths.rootDir}/c_modules`,
				buildDir: `${paths.rootDir}/build`,
			}),
			paths => ({
				tempDir: `${paths.modulesDir}/_temp`,
				frameworksDir: `${paths.modulesDir}/frameworks`,
			}),
		)

		Object.assign(this, {
			cppVersion: 17,
			paths,
		})
	}

	ensureDirs() {
		const { modulesDir, buildDir, tempDir, frameworksDir } = this.paths

		fsShelf.ensureDir(buildDir)

		fsShelf.ensureDir(modulesDir)
		fsShelf.ensureDir(tempDir)
		fsShelf.ensureDir(frameworksDir)
	}
}

// ================================================
const project = new Project()
module.exports = { project, Project }
