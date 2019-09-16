#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

/*
 * 9000 4500 
 * 609 1676
 * 610 588
 * 609 589 
 * 583 1702 
 * 609 1677 
 * 609 588 
 * 609 1677 
 * 608 589 
 * 585 614 
 * 609 1677 
 * 610 588 
 * 585 1678 
 * 609 612 
 * 585 612
 636 560
 611 586
 635 563
 610 586
 585 613
 607 590
 609 588
 608 1680
 608 1679 
 609 615 
 558 613 
 583 614 
 607 592 
 608 614 
 583 1707 
 581 614
 582 1704 
 558 615 
 607 616 
 582 1680 
 606 617 
 578
 19908
 634 615
 608 589
 581 617 
 580 616 
 581 1706 
 583 615 
 582 614 
 582 589 
 606 614
 582 590 
 607 615 
 582 614 
 608 590 
 555 1731 
 582 590 
 607 616 
 581 615 
 582 590 
 606 591 
 606 591 
 607 615 
 584 613 
 594 604 
 583 589 
 609 617
 578 616 
 582 591 
 605 615 
 582 617 
 580 631 
 540 640 
 583 614 
581
 */

// the checking is not as strict as nec_standard, just works...
std::string decode(std::vector<uint32_t> &seqs)
{
  std::vector<bool> buffer = {};
  for (int i = 2; i < 72; i += 2) {
    if (abs((int)seqs[i] - 600) < 100) {
      if (abs((int)seqs[i+1] - 1600) < 200) {
        buffer.push_back(true);
      } else if (abs((int)seqs[i+1] - 600) < 200) {
        buffer.push_back(false);
      } else {
        std::cout << "encountered duration tuple of " << seqs[i] << "," << seqs[i+1] << ", error out\n";
      }
    } else {
      std::cout << "encountered duration of " << seqs[i] << ", index " << i << ", error out\n";
      return "";
    }
  }

  for (int i = 74; i < 138; i += 2) {
    if (abs((int)seqs[i] - 600) < 100) {
      if (abs((int)seqs[i+1] - 1600) < 200) {
        buffer.push_back(true);
      } else if (abs((int)seqs[i+1] - 600) < 200) {
        buffer.push_back(false);
      } else {
        std::cout << "encountered duration tuple of " << seqs[i] << "," << seqs[i+1] << ", error out\n";
      }
    } else {
      std::cout << "encountered duration of " << seqs[i] << ", index " << i << ", error out\n";
      return "";
    }
  }
  auto tochar = [](const bool &b) -> char { if (b) {return '1';} else {return '0';} };

  const int total_length = 35 + 32;
  assert(buffer.size() == total_length);

  char result[total_length + 1];
  result[35] = ' ';
  std::transform(buffer.begin(), buffer.begin() + 35, result, tochar);
  std::transform(buffer.begin() + 36, buffer.end(), result + 36, tochar);
  return std::string(result);
}
