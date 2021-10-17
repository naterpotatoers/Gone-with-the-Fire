import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository, UpdateResult } from 'typeorm';
import { CreateIotDto } from './dto/create-iot.dto';
import { UpdateIotDto } from './dto/update-iot.dto';
import { Iot } from './entities/iot.entity';

@Injectable()
export class IotService {
  constructor(
    @InjectRepository(Iot)
    private repository: Repository<Iot>,
  ) {}

  create(dto: CreateIotDto): Promise<Iot> {
    const iot = new Iot();
    iot.name = dto.name;
    iot.temperature = dto.temperature;
    iot.humidity = dto.humidity;
    iot.longitude = dto.longitude;
    iot.latitude = dto.latitude;
    iot.smoke = dto.smoke;
    return this.repository.save(iot);
  }

  findAll(): Promise<Iot[]> {
    return this.repository.find();
  }

  findOne(id: string): Promise<Iot> {
    return this.repository.findOne(id);
  }

  async update(id: string, dto: UpdateIotDto): Promise<UpdateResult> {
    const iot = await this.findOne(id);
    iot.temperature = dto.temperature;
    iot.humidity = dto.humidity;
    iot.longitude = dto.longitude;
    iot.latitude = dto.latitude;
    iot.smoke = dto.smoke;
    return await this.repository.update(id, iot);
  }

  async remove(id: string): Promise<void> {
    await this.repository.delete(id);
  }
}
