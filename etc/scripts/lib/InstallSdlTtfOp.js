#!/usr/bin/env node

const { Tar, CopyFiles, DownloadArtifact } = require('@almadash/builder')
const {
	BusinessError,
	logger: { simpleLogger: logger },
} = require('@almadash/shelf')
const { fsShelf } = require('@almadash/shelf-node')

const { project } = require('./Project')

// ================================================
/* @info
	- this is the precompiled for macOs
	- archive based install
	- macOs
		+ artifact size: 1.6 Mb
		+ size after extraction: 41.34 Mb
*/
class InstallSdlTtfOp {
	constructor() {
		const { tempDir, modulesDir } = project.paths

		const baseName = 'SDL2_ttf-2.20.2'
		const archiveFile = `${tempDir}/${baseName}.dmg`
		const packageDir = `${tempDir}/${baseName}`

		const includeDir = `${packageDir}/include`
		const keyLinkedFile = `${modulesDir}/asio.hpp`

		const artifactDownload = new DownloadArtifact({
			url: 'https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.dmg',
			filepath: archiveFile,
			dry: false,
		})

		Object.assign(this, {
			archiveFile,
			packageDir,
			artifactDownload,
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
		const { artifactDownload } = this
		await artifactDownload.download()
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
		// await this.extract()
		// await this.link()
	}
}

module.exports = { InstallSdlTtfOp }
