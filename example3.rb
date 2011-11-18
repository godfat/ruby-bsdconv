#!/usr/bin/env ruby

require './bsdconv'

class MyBsdconv < Bsdconv
  def initialize spec
    puts "MyBsdconv created"
    super(spec)
  end
end

p MyBsdconv.new('utf-8:utf-8').conv('test2')
