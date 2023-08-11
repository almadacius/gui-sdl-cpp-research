#!/usr/bin/env node

const nodePath = require('path')

const { Dmg, CopyFiles, DownloadArtifact } = require('@almadash/builder')
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
		+ artifact size: xx Mb
		+ size after extraction: xx Mb
*/
class InstallSdlOp {
	constructor() {
		const { tempDir } = project.paths

		const url = 'https://github.com/libsdl-org/SDL/releases/download/release-2.28.2/SDL2-2.28.2.dmg'
		const baseName = nodePath.basename(url).replace(/\..{3,5}$/, '')

		const frameworkDirName = 'SDL2.framework'

		const mountpoint = `${tempDir}/${baseName}-mounted`
		const extractDir = `${tempDir}/${baseName}`

		const artifactDownload = new DownloadArtifact({
			url,
			filepath: `${tempDir}/${baseName}.dmg`,
			dry: false,
		})

		Object.assign(this, {
			frameworkDirName,
			mountpoint,
			extractDir,
			artifactDownload,
		})
	}

	// ================================================
	async download() {
		const { artifactDownload } = this
		logger.logHeaderBold('download')
		await artifactDownload.download()
	}

	async extract() {
		const { mountpoint, extractDir, artifactDownload } = this
		const { tempDir } = project.paths

		logger.logHeaderBold('extract')
		if (!artifactDownload.exists()) {
			throw new BusinessError('archive NOT found')
		}

		if (fsShelf.dirExists(extractDir)) {
			logger.logHeader('package dir found, SKIP extract')
			return
		}
		logger.logHeader('package dir NOT found, DO extract')

		const dmg = new Dmg({
			baseDir: tempDir,
			targetDir: mountpoint,
			filepath: artifactDownload.filepath,
		})
		await dmg.mount()

		// ================================================
		fsShelf.ensureDir(extractDir)
		const copyFiles = new CopyFiles({
			baseDir: mountpoint,
			destDir: extractDir,
			dry: false,
		})
		await copyFiles.run()

		await dmg.unmount()
	}

	async link() {
		const { extractDir, frameworkDirName } = this
		const { frameworksDir } = project.paths

		logger.logHeaderBold('link')

		const destDir = `${frameworksDir}/${frameworkDirName}`

		if (fsShelf.dirExists(destDir)) {
			logger.logHeader('dest dir found, SKIP linking')
			return
		}
		logger.logHeader('dest dir NOT found, linking')

		const copyFiles = new CopyFiles({
			baseDir: `${extractDir}/${frameworkDirName}`,
			destDir,
			dry: false,
		})
		await copyFiles.run()
	}

	// ================================================
	async install() {
		await this.download()
		await this.extract()
		await this.link()
	}
}

module.exports = { InstallSdlOp }
