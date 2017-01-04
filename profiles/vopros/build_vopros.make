; Make file for building a Vopros installation.

api = 2
core = 7.x

projects[drupal] = drupal
; Remember to update the .po file in translations/.
projects[drupal][version] = 7.53

projects[vopros][type] = "profile"
projects[vopros][download][type] = "git"
projects[vopros][download][url] = "https://github.com/vopros-dk/vopros.git"
