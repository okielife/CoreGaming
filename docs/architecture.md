# Architecture Overview

## Layer boundaries

The engine is split into four layers:

- platform/ — SDL, OS, windowing
- engine/ — pure logic, math, time
- game/ — user code
- assets/ — data only

SDL is intentionally confined to platform/.
Some engine headers include SDL forward declarations where unavoidable.

# Engine Core Systems
