#coding: utf-8

class PMatrix
  def initialize ch, n, m, k
    @ch, @n, @m, @k = ch, n, m, k
  end

  def to_s
    res = "N = #{@n}\nM = #{@m}\nK = #{@k}\n\n"
    0.upto(@n-1) do |i|
      0.upto(@n-1) do |j|
        res += @ch + ((j + 1) % (@n / @m) == 0  && j + (@n / @m) < @n ? ' | ' : ' ' * 3)
      end
      res += "\n"
      if (i + 1) % (@n / @k) == 0 && i + (@n / @k) < @n
        res += '-' * (@n - 1) * 4 + '-' 
      else
        1.upto(@m-1) { |j| res += ' ' * 4 * (@n / @m - 1) + '  | ' } if i != @n - 1
      end
      res += "\n"
    end

    res
  end
end

N, M, K = 10, 2, 3
[
  ['matrix_a', PMatrix.new('a', N, M, K)],
  ['matrix_b', PMatrix.new('b', N, K, M)]
].each do |foo| 
  File.open("#{foo[0]}.mat", 'w') { |f| f.puts foo[1].to_s }
end

