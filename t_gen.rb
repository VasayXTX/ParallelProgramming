#coding: utf-8

class Array
  def to_s; "#{self.join(' ')} "; end
end

class Generator
  T_DIR = 'tests'

  def initialize(name_dir = T_DIR)
    @name_dir = name_dir
    @tests = []
  end

  def add_test(test_in, test_et)
    @tests.push :input => test_in, :etalon =>  test_et
  end

  def generate
    Dir.mkdir(@name_dir) unless Dir.exist? @name_dir
    @tests.each_with_index do |test, i|
      [[test[:input], 'in'], [test[:etalon], 'et']].each do |foo|
        File.open(File.join(@name_dir, "test_#{i}.#{foo[1]}"), 'w') do |f|
          f.puts foo[0].to_s
          f.puts "\n"
        end
      end
    end 
  end
end

