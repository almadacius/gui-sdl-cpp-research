#!/usr/bin/env node

const { GitRepo, CopyFiles } = require('@almadash/builder')
const {
	logger: { simpleLogger: logger },
} = require('@almadash/shelf')
const { fsShelf } = require('@almadash/shelf-node')

const { project } = require('./Project')

// ================================================
class InstallCrowOp {
	constructor() {
		const { tempDir, modulesDir } = project.paths

		const repoDirname = 'crow'
		const repoPath = `${tempDir}/${repoDirname}`

		const includeDir = `${repoPath}/include`
		const keyLinkedFile = `${modulesDir}/crow.h`

		const srcUrl = 'https://github.com/CrowCpp/Crow.git'

		Object.assign(this, {
			repoDirname,
			repoPath,
			srcUrl,
			keyLinkedFile,
			includeDir,
		})
	}

	// ================================================
	hasRepo() {
		const { repoPath } = this
		if (fsShelf.exists(repoPath) && fsShelf.isDirectory(repoPath)) {
			return true
		}
		return false
	}

	hasLinkedFile() {
		const { keyLinkedFile } = this
		return fsShelf.exists(keyLinkedFile)
	}

	// ================================================
	async cloneRepo() {
		const { repoPath, srcUrl } = this
		const { rootDir } = project.paths

		if (this.hasRepo()) {
			logger.logHeader('repo found, SKIP clone')
			return
		}
		logger.logHeader('repo NOT found, DO clone')

		const gitRepo = new GitRepo({ baseDir: rootDir })
		await gitRepo.clone(srcUrl, {
			filepath: repoPath,
		})
	}

	/*
		@info
		- copy `/include/*` into `modulesDir` for actual use
	*/
	async link() {
		const { includeDir } = this
		const { modulesDir } = project.paths

		if (this.hasLinkedFile()) {
			logger.logHeader('key linked file found, SKIP linking')
			return
		}
		logger.logHeader('key linked file NOT found, linking')

		const copyFiles = new CopyFiles({
			baseDir: includeDir,
			destDir: modulesDir,
		})
		const filePaths = await copyFiles.globFiles()
		await copyFiles.copyFiles(filePaths)
	}

	// ================================================
	async install() {
		await this.cloneRepo()
		await this.link()
	}
}

module.exports = { InstallCrowOp }
