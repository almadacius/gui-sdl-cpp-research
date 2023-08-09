#!/usr/bin/env node

const { Dmg, CopyFiles, DownloadArtifact } = require('@almadash/builder')
const {
	BusinessError,
	logger: { simpleLogger: logger },
} = require('@almadash/shelf')
const { fsShelf } = require('@almadash/shelf-node')

const { project } = require('./Project')

// ================================================
/* @info usage
	#include <SDL2_ttf/SDL_ttf.h>
*/
/* @info
	- this is the precompiled for macOs
	- archive based install
	- macOs
		+ artifact size: 1.6 Mb
		+ size after extraction: 3.5 Mb
*/
class InstallSdlTtfOp {
	constructor() {
		const { tempDir } = project.paths

		const baseName = 'SDL2_ttf-2.20.2'
		const mountpoint = `${tempDir}/${baseName}-mounted`
		const extractDir = `${tempDir}/${baseName}`

		const artifactDownload = new DownloadArtifact({
			url: 'https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.dmg',
			filepath: `${tempDir}/${baseName}.dmg`,
			dry: false,
		})

		Object.assign(this, {
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

	/*
		@info
		- copy `/include/*` into `modulesDir` for actual use
	*/
	/* @info
		export CFLAGS="-I/path/to/sdl_ttf_framework/Headers $CFLAGS"
		export LDFLAGS="-F/path/to/sdl_ttf_framework -framework SDL2_ttf $LDFLAGS"
	*/
	async link() {
		const { extractDir } = this
		const { frameworksDir } = project.paths

		logger.logHeaderBold('link')

		const dirname = 'SDL2_ttf.framework'
		const destDir = `${frameworksDir}/${dirname}`

		if (fsShelf.dirExists(destDir)) {
			logger.logHeader('dest dir found, SKIP linking')
			return
		}
		logger.logHeader('dest dir NOT found, linking')

		const copyFiles = new CopyFiles({
			baseDir: `${extractDir}/${dirname}`,
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

module.exports = { InstallSdlTtfOp }
