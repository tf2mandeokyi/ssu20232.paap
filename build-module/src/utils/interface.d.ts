export interface ProjectProperties {
    'zip-rename'?: { [x: string]: string },
    'zip-exclude'?: string[],
    run: { command: string, args?: string[] }[]
}