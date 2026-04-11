# Versioning

Releases are created from **tags**. The GitHub Actions release workflow runs on any tag matching `v*` (e.g. `v1.0.0`).

## CalVer + suffix (recommended unusual scheme)

**Format:** `vYYYY.M.D` or `vYYYY.MM.DD` with optional `-suffix` (codename or pre-release).

- `v2025.3.5` — stable release for that date
- `v2025.3.5-stein` — release with codename
- `v2025.3.5-rc1` — release candidate

Cursor users: the **calver-suffix** project skill (`.cursor/skills/calver-suffix/`) gives tagging commands and conventions.

## Other tag ideas

You can use any tag name that starts with `v` and the workflow will build a release. Some alternatives:

| Style | Example tags | When to use |
|-------|--------------|-------------|
| **CalVer** (calendar) | `v2025.3.5`, `v25.03.05` | Date-based, no “version number” to bump |
| **Zero-based** | `v0.1.0`, `v0.0.3` | “We’re not 1.0 yet” |
| **Single number** | `v1`, `v2`, `v3` | One number, no minor/patch |
| **Codename** | `v1.0.0-stein`, `v2.0.0-gondola` | Pre-release or flavour |
| **Build id** | `v1.0.0+build.42` | Metadata after `+` (often ignored by tools) |
| **Epoch.sequence** | `v1.0`, `v2.0` | Big change = new “epoch” |

**Examples that will trigger the release workflow:**

```bash
git tag -a v1.0.0 -m "First release"
git tag -a v2025.03.05 -m "CalVer: 2025 March 5"
git tag -a v2 -m "Second major"
git push origin v1.0.0 v2025.03.05 v2
```

All of these match `v*`, so each push will create a new GitHub release with Windows and Linux binaries.
