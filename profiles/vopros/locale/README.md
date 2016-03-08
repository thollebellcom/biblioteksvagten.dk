Translation helpers
===================

The Makefile in this directory helps with updating translations.

Usage:

```
make templates
```

Run after code changes.

Extracts strings from modules and profile. Requires the potx module
enabled on the site.


```
make master
```

Run before updating translation strings.

Updates the master da.po with strings from templates.

Edit da.po with a po editor to add/change translations.

```
make translations
```

Run after updating da.po.

Update module po files from master data.
