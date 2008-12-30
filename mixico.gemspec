spec = Gem::Specification.new do |s|
  s.name        = "mixico"
  s.version     = "0.1.0" # whatever
  s.summary     = "mixin hijinks — enable and disable mixins"
  s.files       = Dir['COPYING', 'README', '**/*.rb', '**/*.c']
  s.extensions  = ["ext/mixico/extconf.rb"]
  s.author      = "why the lucky stiff"
  s.email       = "why@ruby-lang.org"
  s.homepage    = "http://github.com/rkh/mixico/tree"
  s.has_rdoc    = false
end