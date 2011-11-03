#coding: utf-8

require './t_gen_sort'
require './t_gen_matrix_mult'

RAND_VAL_RANGE = 0..10 ** 6
MAX_POW = 5

task :g, :goal, :dir do |t, args|
  goals = {
    'sort' => GenSort,
    'matrix_mult' => GenMatrixMult
  }
  args.with_defaults :dir => Generator::T_DIR, :goal => 'sort'

  gen = goals[args[:goal]].new args[:dir]
  gen.create_tests
  gen.generate
end

task :t, :program, :key, :dir do |t, args|
  args.with_defaults :program => 'problem', :dir => Generator::T_DIR, :key => ''

  sf = {
    :in => 'in',
    :out => 'out',
    :etalon => 'et'
  }

  File.delete *Dir["#{args[:dir]}/*.#{sf[:out]}"]
  files_in = Dir["#{args[:dir]}/*.#{sf[:in]}"].map { |name_file| File.basename name_file, ".#{sf[:in]}"}
  files_in.sort!
  files_in.each_with_index do |name_file, i|
    name_f_in = "#{args[:dir]}/#{name_file}.#{sf[:in]}"
    name_f_out = "#{args[:dir]}/#{name_file}.#{sf[:out]}"
    name_f_et = "#{args[:dir]}/#{name_file}.#{sf[:etalon]}"

    a = `./#{args[:program]} #{name_f_in} #{name_f_out} #{args[:key]}`
    res = `diff #{name_f_out} #{name_f_et}`.empty?
    puts "TEST#{i}(#{name_file}.#{sf[:in]}): #{if res then 'OK' else 'ERROR' end}"
  end
end

