spec = Gem::Specification.new do |s|
  s.name        = "mixico"
  s.version     = "0.1.1"
  s.summary     = "mixin hijinks — enable and disable mixins"
  s.description = s.summary
  s.files       = Dir['COPYING', 'README', '**/*.rb', '**/*.c']
  s.extensions  = ["ext/mixico/extconf.rb"]
  s.authors     = ["why the lucky stiff", "Konstantin Haase"]
  s.email       = "konstantin.mailinglists@googlemail.com"
  s.homepage    = "http://github.com/rkh/mixico/tree"
  s.has_rdoc    = false
end