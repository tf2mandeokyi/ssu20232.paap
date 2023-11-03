interface ProjectZipConfig {
    name: string
    rename: { [x: string]: string }
    exclude: string[]
}

interface RunCommand {
    command: string
    args?: string[]
}

interface OsDependantRunCommand {
    default: RunCommand
    [ platform: NodeJS.Platform ]: RunCommand
}

export interface ProjectConfig {
    zip: Partial<ProjectZipConfig>
    run: OsDependantRunCommand[]
}