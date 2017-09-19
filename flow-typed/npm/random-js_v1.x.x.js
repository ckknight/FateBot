// flow-typed signature: 1c3b77431e7bd529b0f9c1537fd6e06f
// flow-typed version: b43dff3e0e/random-js_v1.x.x/flow_>=v0.25.x

declare module 'random-js' {
  declare type Engine = () => number;
  declare type MtEngine = {
    (): number,
    seed(value?: mixed): this,
    seedWithArray(value: mixed[]): this,
    autoSeed(): this,
    discard(count?: number): this,
    getUseCount(): number,
  };
  declare module.exports: {
    integer(
      min: number,
      max: number,
      inclusive?: boolean,
    ): (engine: Engine) => number,
    real(
      min: number,
      max: number,
      inclusive?: boolean,
    ): (engine: Engine) => number,
    bool(): (engine: Engine) => boolean,
    bool(percentage: number): (engine: Engine) => boolean,
    bool(numerator: number, denominator: number): (engine: Engine) => boolean,
    pick<T>(engine: Engine, array: T[], begin?: number, end?: number): T,
    picker<T>(array: T[], begin?: number, end?: number): (engine: Engine) => T,
    shuffle<T>(engine: Engine, array: T[]): T[],
    sample<T>(engine: Engine, array: T[], sampleSize: number): T[],
    die(sideCount: number): (engine: Engine) => number,
    dice(sideCount: number, dieCount: number): (engine: Engine) => number[],
    uuid(engine: Engine): string,
    string(): (engine: Engine, length: number) => string,
    string(pool: string): (length: number, engine: Engine) => string,
    hex(uppercase?: boolean): (length: number, engine: Engine) => string,
    date(start: Date, end: Date): (engine: Engine) => Date,
  };
}
