import {
  Controller,
  Get,
  Post,
  Body,
  Patch,
  Param,
  Delete,
} from '@nestjs/common';
import { IotService } from './iot.service';
import { CreateIotDto } from './dto/create-iot.dto';
import { UpdateIotDto } from './dto/update-iot.dto';

@Controller('iot')
export class IotController {
  constructor(private readonly iotService: IotService) {}

  @Post()
  create(@Body() createIotDto: CreateIotDto) {
    return this.iotService.create(createIotDto);
  }

  @Get()
  findAll() {
    return this.iotService.findAll();
  }

  @Get(':id')
  findOne(@Param('id') id: string) {
    return this.iotService.findOne(id);
  }

  @Patch(':id')
  update(@Param('id') id: string, @Body() updateIotDto: UpdateIotDto) {
    return this.iotService.update(id, updateIotDto);
  }

  @Delete(':id')
  remove(@Param('id') id: string) {
    return this.iotService.remove(id);
  }
}
