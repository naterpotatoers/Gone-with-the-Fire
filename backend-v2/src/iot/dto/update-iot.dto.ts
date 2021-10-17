import { PartialType } from '@nestjs/mapped-types';
import { CreateIotDto } from './create-iot.dto';

export class UpdateIotDto extends PartialType(CreateIotDto) {
  temperature: number;
  humidity: number;
  longitude: number;
  latitude: number;
  smoke: number;
}
