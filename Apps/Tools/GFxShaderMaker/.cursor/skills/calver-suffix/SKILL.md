---
name: calver-suffix
description: ALWAYS use CalVer+suffix when creating git tags in this project. Use when the user wants to set, create, push, or test a version tag, or mentions release naming, CalVer, calendar versioning, or codenames. Do NOT use semver (v1.0.0, v1.0.1-test). Format: vYYYY.M.D[-suffix] e.g. v2025.3.5-test.
---

# CalVer + Suffix

**Always use this format when creating git tags in this project.** Do not use semver (v1.0.0, v1.0.1, v2.0.0).

## Format

- **Base:** `vYYYY.MM.DD` or `vYY.MM.DD` (year.month.day).
- **Suffix (optional):** `-<label>` — codename, `-rc1`, `-alpha`, `-beta`, etc.
- **Full:** `v2025.3.5`, `v2025.03.05-stein`, `v25.3.5-rc1`.

No spaces in the tag; suffix is hyphenated.

## When to use suffix

| Suffix | Use case |
|--------|----------|
| (none) | Stable release for that date |
| `-test` | Test/verification release (e.g. v2025.3.5-test) |
| `-rc1`, `-rc2` | Release candidate |
| `-alpha`, `-beta` | Pre-release |
| `-stein`, `-gondola` | Codename / flavour |

## Git tag (annotated)

```bash
# Today, stable
git tag -a "v$(date +%Y.%-m.%-d)" -m "Release $(date +%Y-%m-%d)"

# With suffix (test, codename, or pre-release)
git tag -a "v2025.3.5-test" -m "Test release 2025-03-05"
git tag -a "v2025.3.5-stein" -m "Release 2025-03-05 (stein)"
git tag -a "v2025.3.5-rc1" -m "Release candidate 1 for 2025-03-05"

# Push
git push origin --tags
```

**Windows (PowerShell)** for "today" (with optional suffix):

```powershell
$d = Get-Date; $ver = "v$($d.Year).$($d.Month).$($d.Day)"; git tag -a $ver -m "Release $($d.ToString('yyyy-MM-dd'))"; git push origin $ver
# With suffix (e.g. -test):
$d = Get-Date; $ver = "v$($d.Year).$($d.Month).$($d.Day)-test"; git tag -a $ver -m "Test release $($d.ToString('yyyy-MM-dd'))"; git push origin $ver
```

## Release title / name

For GitHub Releases or similar, derive from the tag:

- Tag `v2025.3.5` → title **2025.03.05** or **v2025.3.5**
- Tag `v2025.3.5-stein` → title **2025.03.05 (stein)** or **v2025.3.5-stein**

Prefer zero-padded in titles for sort order: `2025.03.05`.

## Summary

- **CalVer:** date in tag = `vYYYY.MM.DD` (or `vYY.M.M`).
- **Suffix:** optional `-name` or `-rcN` / `-alpha` / `-beta`.
- Tag format: `v<calver>[-<suffix>]`; push with `git push origin <tag>`.
