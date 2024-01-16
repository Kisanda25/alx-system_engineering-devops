# Using strance to fix error 

$file_to_edit = '/var/www/html/wp-settings.php'

#fixing phpp to php

exec { 'replace_line':
  command => "sed -i 's/phpp/php/g' ${file_to_edit}",
  path    => ['/bin','/usr/bin']
}
