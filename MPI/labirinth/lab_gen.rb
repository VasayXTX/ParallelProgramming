#coding: utf-8
#
#Ruby-script to generate labirinth

#Labitinth_1
l1 = {
  :size => 10,
  :entry => [1, 1],
  :exit => [10, 10],
  :walls => [
    [6, 8..10],
    [2, 6],
    [2, 4, 6..9],
    [2, 4],
    [2, 4..10],
    [2..4],
    [4],
    [2, 4],
    [2, 4, 6],
    [2, 6]
  ]
}

def make_line n, w
  foo = []
  w.each { |el| el.instance_of?(Range) ? foo.concat(el.to_a) : foo << el }
  (Array.new(n) { |i| foo.include?(i+1) ? '#' : '.' }).join('')
end

def print_lab f_name, l
  File.open(f_name, "w") do |f|
    f.puts l[:size]
    l[:walls].each_with_index do |w, i|
      line = make_line l[:size], w
      line[l[:entry][1]-1] = '*' if i == l[:entry][0] - 1
      line[l[:exit][1]-1] = 'E' if i == l[:exit][0] - 1
      f.puts line
    end
    f.puts 
  end
end

print_lab "input.txt", l1

