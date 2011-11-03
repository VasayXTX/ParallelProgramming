#coding: utf-8

class TestMatrixMultIn
  def initialize(m1, m2); @m1, @m2 = m1, m2; end
  def to_s; "#{@m1.size.to_s}\n#{@m1.to_s}\n#{@m2.to_s}"; end
end

class GenMatrixMult < Generator
  def create_tests
    make_test_seq = ->(el_count, *arr_p) do
      m = arr_p.map do |p|
        Array.new(el_count ** 2) do |i|
          p.call i / el_count, i % el_count
        end
      end
      [TestMatrixMultIn.new(m[0], m[1]), m[2]]
    end
    
    #Test1
    add_test *make_test_seq.(
      1,
      Proc.new { |i, j| 0.1 },
      Proc.new { |i, j| 0.2 },
      Proc.new { |i, j| 0.02 }
    )

    #Test2
    add_test *make_test_seq.(
      2,
      Proc.new { |i, j| 0.1 },
      Proc.new { |i, j| 0.2 },
      Proc.new { |i, j| 0.04 }
    )

    #Test3
    add_test *make_test_seq.(
      100,
      Proc.new { |i, j| 0.1 },
      Proc.new { |i, j| 0.2 },
      Proc.new { |i, j| 2 }
    )

    #Test4
    add_test *make_test_seq.(
      1000,
      Proc.new { |i, j| i == j ? 0 : 0.1 },
      Proc.new { |i, j| i == j ? 0 : 0.2 },
      Proc.new { |i, j| i == j ? 19.98 : 19.96 }
    )
  end
end

