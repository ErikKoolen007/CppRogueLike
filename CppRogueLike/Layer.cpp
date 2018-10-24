#include "Layer.h"
#include "Utilities.h"
#include "Hallway.h"

const Room* Layer::get_start() const
{
	return start_;
}

const Room* Layer::get_end() const
{
	return end_;
}

const Room* Layer::get_rooms() const
{
	return rooms_;
}

void Layer::set_start(Room& start)
{
	start_ = &start;
}

void Layer::set_end(Room& end)
{
	end_ = &end;
}

void Layer::generate_random_layer()
{
	int number { 1 };

	for (int row{}; row < y_; row++)
	{
		for (int column{}; column < x_; column++)
		{
			//Create rooms with a state, layer number and room number
			rooms_[row * x_ + column] = Room{ 3, layer_nr_, number };
			number++;

			//Create hallways
			if (column >= 1)
			{
				const int previous_column{ column - 1 };

				//First create right hallway of previous room in same row
				*rooms_[row * x_ + previous_column].get_hallway(1) = Hallway(Utilities::get_random(1, 9), rooms_[row * x_ + previous_column], rooms_[row * x_ + column]);

				//Then set leftEdge of current vertex to previous vertex's rightEdge
				*rooms_[row * x_ + column].get_hallway(3) = *rooms_[row * x_ + previous_column].get_hallway(1);
			}
			if (row >= 1)
			{
				const int previous_row{ row - 1 };

				//First create down edge of vertex in same column but previous row
				*rooms_[previous_row * x_ + column].get_hallway(2) = Hallway(Utilities::get_random(1, 9), rooms_[previous_row * x_ + column], rooms_[row * x_ + column]);

				//Then set upEdge of current vertex to previous vertex's downEdge
				*rooms_[row * x_ + column].get_hallway(0) = *rooms_[previous_row * x_ + column].get_hallway(2);
			}
		}
	}
	//Create start
	start_ = &rooms_[Utilities::get_random(0, x_ * y_ - 1)];
	start_->set_state(0);

	//Create end
	end_ = &rooms_[Utilities::get_random(0, x_ * y_ - 1)];

	//If start == end -> find another end
	while (end_->get_number() == start_->get_number())
	{
		end_ = &rooms_[Utilities::get_random(0, x_ * y_ - 1)];
	}
	end_->set_state(4);

	//DrawMap(x);
}
