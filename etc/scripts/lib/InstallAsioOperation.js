#!/usr/bin/env node

const { Wget, Tar, CopyFiles } = require('@almadash/builder')
const {
	BusinessError,
	logger: { simpleLogger: logger },
} = require('@almadash/shelf')
const { fsShelf } = require('@almadash/shelf-node')

const { project } = require('./Project')

// ================================================
class InstallAsioOperation {
	constructor() {
		const { tempDir, modulesDir } = project.paths

		const archiveFile = `${tempDir}/asio-1.28.0.tar.bz2`
		const packageDir = `${tempDir}/asio-1.28.0`

		const includeDir = `${packageDir}/include`
		const keyLinkedFile = `${modulesDir}/asio.hpp`

		const srcUrl = 'https://sourceforge.net/projects/asio/files/asio/1.28.0%20%28Stable%29/asio-1.28.0.tar.bz2/download'

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
		await tar.extractBzip2({
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
		await this.link()
	}
}

module.exports = { InstallAsioOperation }
