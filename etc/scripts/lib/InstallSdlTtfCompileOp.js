#!/usr/bin/env node

const { Wget, Tar, CopyFiles } = require('@almadash/builder')
const {
	BusinessError,
	logger: { simpleLogger: logger },
} = require('@almadash/shelf')
const { fsShelf } = require('@almadash/shelf-node')

const { project } = require('./Project')

// ================================================
/* @info
	- archive based install
	- @partial
		+ this is the source for compiling
		+ I want the precompiled
	- macOs
		+ artifact size: 13.16 Mb
		+ size after extraction: 41.34 Mb
*/
class InstallSdlTtfCompileOp {
	constructor() {
		const { tempDir, modulesDir } = project.paths

		const baseName = 'SDL2_ttf-2.20.2'
		const archiveFile = `${tempDir}/${baseName}.tar.gz`
		const packageDir = `${tempDir}/${baseName}`

		const includeDir = `${packageDir}/include`
		const keyLinkedFile = `${modulesDir}/asio.hpp`

		const srcUrl = 'https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.tar.gz'

		Object.assign(this, {
			archiveFile,
			packageDir,
			srcUrl,
			includeDir,
			keyLinkedFile,
		})
	}

	// ================================================
	hasArchive() {
		const { archiveFile } = this
		return fsShelf.exists(archiveFile)
	}

	hasLinkedFile() {
		const { keyLinkedFile } = this
		return fsShelf.exists(keyLinkedFile)
	}

	// ================================================
	async download() {
		const { srcUrl, archiveFile } = this
		const { rootDir } = project.paths

		if (this.hasArchive()) {
			logger.logHeader('archive found, SKIP download')
			return
		}
		else {
			logger.logHeader('archive NOT found, DO download')
		}

		const wget = new Wget({ baseDir: rootDir })
		await wget.download(srcUrl, {
			filepath: archiveFile,
		})
	}

	async extract() {
		const { archiveFile, packageDir } = this
		const { tempDir } = project.paths

		if (!this.hasArchive()) {
			throw new BusinessError('archive not found')
		}
		logger.logHeader('archive found')

		if (fsShelf.exists(packageDir) && fsShelf.isDirectory(packageDir)) {
			logger.logHeader('package dir already exists, SKIP extract')
			return
		}
		logger.logHeader('package dir does NOT exist, DO extract')

		const tar = new Tar({ baseDir: tempDir })
		await tar.extractGz({
			filepath: archiveFile,
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
		const filePaths = await copyFiles.globFiles({
			excludePatterns: [
				/^Makefile/,
			],
		})
		await copyFiles.copyFiles(filePaths)
	}

	// ================================================
	async install() {
		await this.download()
		await this.extract()
		// await this.link()
	}
}

module.exports = { InstallSdlTtfCompileOp }
