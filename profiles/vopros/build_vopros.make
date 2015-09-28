; Make file for building a Vopros installation.

api = 2
core = 7.x

projects[drupal] = drupal
projects[drupal][version] = 7.39

projects[vopros][type] = "profile"
projects[vopros][download][type] = "git"
projects[vopros][download][url] = "https://github.com/DBCDK/Vopros-install.git"
