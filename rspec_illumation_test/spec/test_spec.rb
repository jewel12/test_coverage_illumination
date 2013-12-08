describe 'Illumination Test' do
  coverage = 100
  100.times do |i|
    expected = i >= coverage ? false : true
    it "test #{i}" do
      expect(true).to eq(expected)
    end
  end
end
