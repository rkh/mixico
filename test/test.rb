direc = File.dirname(__FILE__)
require 'rubygems'
require 'bacon'
require "#{direc}/../lib/mixico"

puts "Testing Mixico version #{Mixico::VERSION}..."
puts "Ruby version #{RUBY_VERSION}"
describe Mixico do
  before do
    @m = Module.new {
      def hello
        :hello
      end
    }
  end

  it 'should provide a mix_eval method to Object' do
    Object.method_defined?(:mix_eval).should.equal true
  end

  it 'should make "hello" method available to block' do
    mix_eval(@m) {  should.respond_to(:hello) }
  end

  it 'should make "hello" method unavailable outside the block' do
    mix_eval(@m) { hello }
    should.not.respond_to(:hello)
  end

  it 'should makke "hello" method return :hello' do
    mix_eval(@m) { hello.should.equal :hello }
  end
end

  
  
