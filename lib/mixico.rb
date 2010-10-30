# mixico.rb
# added by John Mair (banisterfiend) 2010
# License: MIT

direc = File.dirname(__FILE__)

begin
  if RUBY_VERSION && RUBY_VERSION =~ /1.9/
    require "#{direc}/1.9/mixico"
  else
    require "#{direc}/1.8/mixico"
  end
rescue LoadError => e
  require 'rbconfig'
  dlext = Config::CONFIG['DLEXT']
  require "#{direc}/mixico.#{dlext}"
end

require "#{direc}/mixico/version"

class Proc

  # The context of the block
  # @return [Object] The value of *self* inside the block
  def __context__
    eval('self', binding)
  end
  
  # indicates whether the module *mod* is currently mixed in to the receiver
  # @param [Module] mod The module to check for inclusion
  # @return [Boolean] True if the module is included, false if not
  def includes_mixin? mod
    (class << __context__; self end).include? mod
  end

  # Mixes a module into the context of the Proc
  # @param [Module] mod The module to mix in
  # @example
  #   def hello(&block)
  #     block.mixin MyModule
  #   end
  def mixin mod 
    __context__.extend mod
  end

  # Removes a module from the context of the Proc
  # @param [Module] mod The module to remove from the Proc context.
  # @example
  #   def hello(&block)
  #     block.mixin MyModule
  #     block.mixout MyModule
  #   end
  def mixout mod
    (class << __context__; self end).disable_mixin mod
  end 
end

class Object

  # Mixes a module into the block, executes the block, unmixes the
  # module.
  #
  # @example
  #   module Hello
  #     def hello
  #       puts "hello"
  #     end
  #   end
  #   mix_eval(Hello) { hello } #=> "hello"
  #   hello #=> NameError
  # @param [Module] mod The module to mix into the block
  # @yield The block will be executed with the module mixed in.
  # @return The value of the block
  def mix_eval mod, &blk
    if blk.includes_mixin? mod 
      blk.call 
    else 
      blk.mixin mod 
      begin 
        blk.call
      ensure
        blk.mixout mod
      end
    end
  end
end 
