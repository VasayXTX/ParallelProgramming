#coding: utf-8

require './t_gen'

class TestSortIn
  def initialize(arr); @arr = arr; end
  def to_s; "#{@arr.size.to_s}\n#{@arr.to_s}"; end
end

class GenSort < Generator
  def create_tests
    make_test_seq = ->(el_count, p_in, p_et) do
      a = Array.new(el_count) { |i| p_in.call(i) }
      [TestSortIn.new(a), p_et.call(a)]
    end

    #Test1, Test2, Test3
    [1, 10 ** 2, 10 ** MAX_POW].each do |c|
      add_test *make_test_seq.(
        c,
        Proc.new { |i| i },
        Proc.new { |a| a }
      )
    end

    #Test4, Test5
    [10 ** 2, 10 ** MAX_POW].each do |c|
      add_test *make_test_seq.(
        c,
        Proc.new { |i| c - i - 1 },
        Proc.new { |a| a.reverse }
      )
    end

    #Test6, Test7
    r = Random.new
    [10 ** 2, 10 ** MAX_POW].each do |c| 
      add_test *make_test_seq.(
        c,
        p_in = Proc.new { |i| r.rand(RAND_VAL_RANGE) },
        p_et = Proc.new { |a| a.sort }
      )
    end
  end
end

