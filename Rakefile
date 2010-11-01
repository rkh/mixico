# -*- coding: utf-8 -*-
direc = File.dirname(__FILE__)
dlext = Config::CONFIG['DLEXT']

require 'rake/clean'
require 'rake/gempackagetask'
require './lib/mixico/version'

CLEAN.include("ext/**/*.#{dlext}", "ext/**/*.log", "ext/**/*.o", "ext/**/*~", "ext/**/*#*", "ext/**/*.obj", "ext/**/*.def", "ext/**/*.pdb")
CLOBBER.include("**/*.#{dlext}", "**/*~", "**/*#*", "**/*.log", "**/*.o")

def apply_spec_defaults(s)
  s.name        = "mixico"
  s.version     = Mixico::VERSION
  s.summary     = "mixin hijinks — enable and disable mixins"
  s.description = s.summary
  s.files       = Dir['COPYING', 'README', '**/*.rb', '**/*.c', '**/*.h']
  s.authors     = ["why the lucky stiff", "Konstantin Haase", "John Mair (banisterfiend)"]
  s.email       = "konstantin.mailinglists@googlemail.com"
  s.homepage    = "http://github.com/rkh/mixico/tree"
  s.has_rdoc    = 'yard'
end

task :test do
  sh "bacon -k #{direc}/test/test.rb"
end

[:mingw32, :mswin32].each do |v|
  namespace v do
    spec = Gem::Specification.new do |s|
      apply_spec_defaults(s)        
      s.platform = "i386-#{v}"
      s.files += FileList["lib/**/*.#{dlext}"].to_a
    end

    Rake::GemPackageTask.new(spec) do |pkg|
      pkg.need_zip = false
      pkg.need_tar = false
    end
  end
end

namespace :ruby do
  spec = Gem::Specification.new do |s|
    apply_spec_defaults(s)        
    s.platform = Gem::Platform::RUBY
    s.extensions = ["ext/mixico/extconf.rb"]
  end

  Rake::GemPackageTask.new(spec) do |pkg|
    pkg.need_zip = false
    pkg.need_tar = false
  end
end



