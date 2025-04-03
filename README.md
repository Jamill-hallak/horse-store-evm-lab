# 🐴 Horse Store EVM Lab

This repository explores low-level smart contract development using **Solidity**, **Yul**, and **Huff**, with a focus on understanding how EVM opcodes behave and how different compilers generate bytecode.

> 💡 This project is based on concepts from the [Updraft by Cyfrin](https://updraft.cyfrin.io/) course. It expands on those lessons with deeper organization, multi-version comparisons, and professional structuring.

---

## 🔍 What’s Inside

The **Horse Store** contract is implemented in multiple forms and versions to help you compare:

### `src/horsestore/v1/`
- `HorseStore.sol` – High-level Solidity version.
- `HorseStoreYul.sol` – Solidity using inline Yul blocks.
- `HorseStoreYul.yul` – Pure Yul contract (stored separately under `/Yul/`).
- `horsestore.huff` – Huff version of the contract.
- `IHorseStore.sol` – Shared interface.

### `src/horsestore/v2/`
- `HorseStore.sol` – Improved  design.
- `HorseStore.huff` – Optimized Huff version.
- `why.huff` – Experimental Huff logic.
- `IHorseStore.sol` – Interface for version 2.

---

## ⚒️ Tooling

You’ll need the following installed:

- [Foundry](https://book.getfoundry.sh/)
- [Huff Compiler](https://docs.huff.sh/)
- [Solidity Compiler (solc)](https://soliditylang.org/)
- [Halmos (optional for formal verification)](https://github.com/Cyfrin/halmos)

---

## 🚀 Getting Started

```bash
git clone https://github.com/Jamill-hallak/horse-store-evm-lab.git
cd horse-store-evm-lab
make            # or manually install dependencies
forge test      # run tests
```

To compile manually:

```bash
# Huff
huffc src/horsestore/v1/horsestore.huff -b

# Yul (strict assembly)
solc --strict-assembly --optimize --optimize-runs 20000 src/Yul/HorseStoreYul.yul --bin

# Solidity with Yul
solc --optimize --optimize-runs 20000 src/horsestore/v1/HorseStoreYul.sol --bin
```

---

## 🎯 Purpose

This repo is meant to:
- Teach the differences between Solidity, Yul, and Huff implementations
- Reveal how compiler outputs vary in gas efficiency and opcode structure
- Prepare you to think like an EVM-level smart contract engineer

---

## 🧠 Inspired by

[Updraft – Cyfrin's Formal Verification and EVM Internals Course](https://updraft.cyfrin.io/)

---

## 📬 Connect

- [GitHub](https://github.com/Jamill-hallak)
- [Portfolio](https://jamillhallak.com/)
- [LinkedIn](https://www.linkedin.com/in/jamill-hallak/)
