import unittest

def add(x, y):
  """Adds two numbers."""
  return x + y

class TestAdd(unittest.TestCase):

  def test_add_positive(self):
    """Tests addition of positive numbers."""
    result = add(2, 3)
    self.assertEqual(result, 5)

  def test_add_negative(self):
    """Tests addition of negative numbers."""
    result = add(-2, -4)
    self.assertEqual(result, -6)

if __name__ == '__main__':
  unittest.main()
