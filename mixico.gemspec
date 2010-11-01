# -*- coding: utf-8 -*-
direc = File.dirname(__FILE__)
require "#{direc}/lib/mixico/version"

spec = Gem::Specification.new do |s|
  s.name        = "mixico"
  s.version     = Mixico::VERSION
  s.summary     = "mixin hijinks — enable and disable mixins"
  s.description = s.summary
  s.files       = Dir['COPYING', 'README', '**/*.rb', '**/*.c', '**/*.h'] +
    ['lib/1.8/mixico.so', 'lib/1.9/mixico.so']
  #s.extensions  = ["ext/mixico/extconf.rb"]
  s.platform = 'i386-mingw32'
  s.authors     = ["why the lucky stiff", "Konstantin Haase", "John Mair (banisterfiend)"]
  s.email       = "konstantin.mailinglists@googlemail.com"
  s.homepage    = "http://github.com/rkh/mixico/tree"
  s.has_rdoc    = 'yard'
end
