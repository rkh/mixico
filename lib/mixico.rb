require 'cmixico'

class Proc
  def includes_mixin? mod
    (class << binding.eval('self'); self end).include? mod
  end 
  def mixin mod 
    binding.eval('self').extend mod
  end 
  def mixout mod
    (class << binding.eval('self'); self end).disable_mixin mod
  end 
end

class Object
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
